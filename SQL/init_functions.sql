CREATE OR REPLACE FUNCTION logowanie_gracza_wykonaj(login_var VARCHAR(70), haslo_var VARCHAR(30)) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	message_ret TEXT,
	id_gracza_ret BIGINT,
	imie_ret TEXT,
	poziom_ret INT, 
	doswiadczenie_ret BIGINT, 
	doswiadczenie_nastepny_poziom_ret BIGINT,
	punkty_do_rozdania_ret INT
)  
AS $$
DECLARE 
	id_gracza_var BIGINT;
	ban_data_do_var DATE;
	imie_var TEXT; 
BEGIN
	
	--czy gracz istnieje
	SELECT id_gracza, imie INTO id_gracza_var, imie_var FROM gracze WHERE email = login_var AND aktywny=TRUE;
	IF NOT FOUND THEN
		RETURN QUERY SELECT FALSE, 'Podany gracz nie istnieje.'::TEXT, NULL::BIGINT, NULL::TEXT, NULL::INT, NULL::BIGINT, NULL::BIGINT, NULL::INT;
		RETURN;
	END IF;
	
	--czy haslo pasuje do konta
	IF NOT EXISTS(SELECT 1 FROM gracze WHERE id_gracza=id_gracza_var AND haslo = haslo_var) THEN
		RETURN QUERY SELECT FALSE, 'Podane haslo nie pasuje.'::TEXT, NULL::BIGINT, NULL::TEXT, NULL::INT, NULL::BIGINT, NULL::BIGINT, NULL::INT;
		RETURN;
	END IF;
	
	--czy gracz ma bana
	SELECT data_do INTO ban_data_do_var FROM gracze_bany WHERE id_gracza=id_gracza_var AND NOW() BETWEEN data_od AND data_do AND aktywny=TRUE;
	IF FOUND THEN
		RETURN QUERY SELECT FALSE, ('Konto gracza ' || imie_var || ' posiada bana do dnia ' || ban_data_do_var)::TEXT, NULL::BIGINT, NULL::TEXT, NULL::INT, NULL::BIGINT, NULL::BIGINT, NULL::INT;
		RETURN;
	END IF;
	
	--Ustawianie gracza jako On-Line
	UPDATE gracze SET status_online=TRUE WHERE id_gracza=id_gracza_var;
	
	--pobieranie informacji o graczu
	RETURN QUERY SELECT 
		TRUE,
		'OK'::TEXT,
		id_gracza_var,
		imie_var, 
		gp.poziom,
		gp.doswiadczenie,
		gp.doswiadczenie_nastepny_poziom,
		gp.punkty_do_rozdania
	FROM
		gracze g
		INNER JOIN gracze_poziomy gp ON gp.id_gracza=g.id_gracza
	WHERE 
		g.id_gracza=id_gracza_var;
END;
$$  LANGUAGE 'plpgsql';


CREATE OR REPLACE FUNCTION wylogowanie_gracza_wykonaj(id_gracza_var BIGINT) RETURNS 
BOOLEAN
AS $$
BEGIN
	--Ustawianie gracza jako Off-Line
	UPDATE gracze SET status_online=FALSE WHERE id_gracza=id_gracza_var;
	
	RETURN TRUE;
END;
$$  LANGUAGE 'plpgsql';

--ZMIANA
CREATE OR REPLACE FUNCTION pobierz_liste_potworow(id_gracza_var BIGINT, lp_var BIGINT, offset_var INT) RETURNS 
TABLE
(
	id_potwor_gracza_ret BIGINT,
	nazwa_ret TEXT,
	opis_ret TEXT,
	tekstura_ret BYTEA,
	zdrowie_ret INT,
	ochrona_ret INT,
	atak_ret INT,
	punkty_ruchu_ret INT
)  
AS $$
BEGIN
	RETURN QUERY 
		SELECT
			gp.id_gracz_potwor,
			p.nazwa::TEXT,
			p.opis,
			p.texture,
			gp.zdrowie,
			gp.ochrona,
			gp.atak,
			gp.punkty_ruchu
		FROM 
			gracze_potwory gp
			INNER JOIN potwory p ON p.id_potwora = gp.id_potwora 
		WHERE
			gp.id_gracza = id_gracza_var
		ORDER BY 1 OFFSET lp_var ROWS FETCH NEXT 3 ROWS ONLY; --FIXME: in place of 3 insert variable 'offset_var' meybe use CURSOR
END;
$$  LANGUAGE 'plpgsql';

--ZMIANA
CREATE OR REPLACE FUNCTION aktualizacja_potwora_wykonaj(id_potwor_gracza_ret BIGINT, zdrowie_var INT, obrona_var INT, atak_var INT, punkty_ruchu_var INT) RETURNS 
BOOLEAN
AS $$
DECLARE 
	id_gracza_var BIGINT;
	ilosc_przypisanych_punktow_var INT;
	zdrowie_var_temp INT;
	ochrona_var_temp INT;
	atak_var_temp INT;
	punkty_ruchu_var_temp INT;
BEGIN
	
	SELECT id_gracza, zdrowie, ochrona, atak, punkty_ruchu INTO id_gracza_var, zdrowie_var_temp, ochrona_var_temp, atak_var_temp, punkty_ruchu_var_temp FROM gracze_potwory WHERE id_gracz_potwor=id_potwor_gracza_ret;
	
	ilosc_przypisanych_punktow_var := (zdrowie_var - zdrowie_var_temp) + (obrona_var - ochrona_var_temp) + (atak_var - atak_var_temp) + (punkty_ruchu_var - punkty_ruchu_var_temp);

	UPDATE gracze_potwory SET zdrowie=zdrowie_var, ochrona=obrona_var, atak=atak_var, punkty_ruchu=punkty_ruchu_var WHERE id_gracz_potwor=id_potwor_gracza_ret;
	
	UPDATE gracze_poziomy SET punkty_do_rozdania=punkty_do_rozdania-ilosc_przypisanych_punktow_var WHERE id_gracza = id_gracza_var;
	
	RETURN TRUE;
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION pobierz_dane_gracza(id_gracza_var BIGINT) RETURNS 
TABLE
(
	imie_ret TEXT,
	poziom_ret INT, 
	doswiadczenie_ret BIGINT, 
	doswiadczenie_nastepny_poziom_ret BIGINT,
	punkty_do_rozdania_ret INT
)  
AS $$
BEGIN
	--pobieranie informacji o graczu
	RETURN QUERY SELECT 
		g.imie::TEXT, 
		gp.poziom,
		gp.doswiadczenie,
		gp.doswiadczenie_nastepny_poziom,
		gp.punkty_do_rozdania
	FROM
		gracze g
		INNER JOIN gracze_poziomy gp ON gp.id_gracza=g.id_gracza
	WHERE 
		g.id_gracza=id_gracza_var;
END;
$$  LANGUAGE 'plpgsql';

--zmiana
CREATE OR REPLACE FUNCTION abort_waiting(id_player_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE 
	id_gracza_oczekujacego_var BIGINT;
	czeka_var BOOLEAN;
BEGIN
	
	IF NOT EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var) THEN
		RETURN QUERY SELECT FALSE, 1, 'Brak oczekującego gracza o podanym identyfikatorze.'::TEXT;
		RETURN;
	END IF;
	
	id_gracza_oczekujacego_var := (SELECT id_gracza_oczekujacego FROM gracze_oczekujacy WHERE id_gracza=id_player_var);
	
	czeka_var := (SELECT czeka FROM gracze_oczekujacy WHERE id_gracza=id_player_var);
	
	IF czeka_var=FALSE THEN
		RETURN QUERY SELECT FALSE, 2, 'Gracz jest w trakcie rozgrywki.'::TEXT;
		RETURN;
	END IF;
	
	DELETE FROM potwory_graczy_oczekujacych WHERE id_gracza_oczekujacego=id_gracza_oczekujacego_var;
	
	DELETE FROM gracze_oczekujacy WHERE id_gracza_oczekujacego=id_gracza_oczekujacego_var;
	
	
	RETURN QUERY SELECT TRUE, 3, 'Przerwano oczekiwanie.'::TEXT;
	RETURN;
	
END;
$$  LANGUAGE 'plpgsql';

--zmiana
CREATE OR REPLACE FUNCTION set_waiting_creature(id_creature_var BIGINT, id_element_var INT, pos_x_var INT, pos_y_var INT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN

	INSERT INTO potwory_graczy_oczekujacych VALUES(DEFAULT, NULL, id_creature_var, id_element_var, pos_x_var, pos_y_var);

	RETURN QUERY SELECT TRUE, 1, 'OK.'::TEXT;
	RETURN;
	
END;
$$  LANGUAGE 'plpgsql';	

--zmiana
CREATE OR REPLACE FUNCTION delete_waiting_creature(id_creature_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN

	DELETE FROM potwory_graczy_oczekujacych WHERE id_gracz_potwor = id_creature_var;

	RETURN QUERY SELECT TRUE, 1, 'OK.'::TEXT;
	RETURN;
	
END;
$$  LANGUAGE 'plpgsql';	

--zmiana
CREATE OR REPLACE FUNCTION set_waiting_player(id_player_var BIGINT, id_game_mode_var INT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE 
	id_gracza_oczekujacego_var BIGINT;
	count_player_var INT;
	min_count_player_var INT;
	max_count_player_var INT;
BEGIN
	
	IF EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var AND czeka=TRUE) THEN
		RETURN QUERY SELECT FALSE, 1, 'Gracz o podanym identyfikatorze czeka na rozgrywke.'::TEXT;
		RETURN;
	END IF;
	
	IF EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var AND czeka=FALSE) THEN
		RETURN QUERY SELECT FALSE, 2, 'Gracz o podanym identyfikatorze jest podczas rozgrywki.'::TEXT;
		RETURN;
	END IF;
	
	count_player_var := (SELECT count(*) FROM potwory_graczy_oczekujacych WHERE id_gracz_potwor IN (SELECT id_gracz_potwor FROM gracze_potwory WHERE id_gracza=id_player_var));
	
	min_count_player_var := (SELECT wartosc::INT FROM konfiguracja_systemu WHERE nazwa='MIN_COUNT_CREATURE');
	max_count_player_var := (SELECT wartosc::INT FROM konfiguracja_systemu WHERE nazwa='MAX_COUNT_CREATURE');
	
	IF min_count_player_var  > count_player_var THEN
		RETURN QUERY SELECT FALSE, 3, 'Za malo postawionych pionkow'::TEXT;
		RETURN;
	END IF;
	
	IF max_count_player_var  < count_player_var THEN
		RETURN QUERY SELECT FALSE, 4, 'Za duzo postawionych pionkow'::TEXT;
		RETURN;
	END IF;
	
	INSERT INTO gracze_oczekujacy VALUES(DEFAULT, id_player_var, id_game_mode_var, NOW(), true, NOW()) RETURNING id_gracza_oczekujacego INTO id_gracza_oczekujacego_var;
	
	UPDATE potwory_graczy_oczekujacych SET id_gracza_oczekujacego=id_gracza_oczekujacego_var WHERE id_gracza_oczekujacego IS NULL AND id_gracz_potwor IN
	(
        SELECT id_gracz_potwor FROM gracze_potwory WHERE id_gracza=id_player_var
    ); 

	RETURN QUERY SELECT TRUE, 5, 'OK.'::TEXT;
	RETURN;
	
END;
$$  LANGUAGE 'plpgsql';


CREATE OR REPLACE FUNCTION get_waiting_info(id_player_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT, 
	id_bitwy_ret BIGINT
)  
AS $$
DECLARE 
	id_gracza_oczekujacego_var BIGINT;
	id_game_mode_var INT;
	level_player_var INT;
	level_enemy_min_var INT;
	level_enemy_max_var INT;
	difference_enemy_var INT;
	number_waiting_enemy_var INT;
	number_waiting_enemy_to_start_game_var INT; 
	name_enemy_var TEXT;
	id_bitwy_var BIGINT;
	max_number_maps_var BIGINT;
	number_drawn_map BIGINT;
	id_drawn_map BIGINT;
BEGIN
	
	--czy gracz jest w tabeli 'gracze_oczekujacy'
	IF NOT EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var) THEN
		RETURN QUERY SELECT FALSE, 1, 'Brak oczekujacego gracza o podanym identyfikatorze.'::TEXT, NULL;
		RETURN;
	END IF;
	
	--Czy gracz jest podczas rozgrywki (musi spelniac warunki: nie czekac i byc w bitwie)
	IF EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var AND czeka=FALSE) AND EXISTS(SELECT 1 FROM bitwy_gracze WHERE id_gracza=id_player_var AND id_typ_wyniku_bitwy IS NULL) THEN
		id_bitwy_var := (SELECT id_bitwy FROM bitwy_gracze WHERE id_gracza=id_player_var AND id_typ_wyniku_bitwy IS NULL);
		RETURN QUERY SELECT TRUE, 4, 'Za chwile rozpocznie sie gra.'::TEXT, id_bitwy_var;
		RETURN;
	END IF;
	
	id_game_mode_var := (SELECT id_typ_rozgrywki FROM gracze_oczekujacy WHERE id_gracza=id_player_var AND czeka=TRUE);
	number_waiting_enemy_to_start_game_var := (SELECT liczba_wymaganych_przeciwnikow FROM typy_rozgrywki WHERE id_typ_rozgrywki=id_game_mode_var);
	level_player_var := (SELECT poziom FROM gracze_poziomy WHERE id_gracza=id_player_var);
	
	difference_enemy_var := (SELECT wartosc::INT FROM konfiguracja_systemu WHERE nazwa='DIFFRENCE_LEVEL_ENEMY');
	level_enemy_min_var := level_player_var - difference_enemy_var;
	level_enemy_max_var := level_player_var + difference_enemy_var;
	
	CREATE TEMP TABLE IF NOT EXISTS tmp_table_enemy_var AS
					SELECT 
						g.imie, g.id_gracza
					FROM 
						gracze_oczekujacy go 
						INNER JOIN gracze g ON go.id_gracza=g.id_gracza
						INNER JOIN gracze_poziomy gp ON gp.id_gracza=g.id_gracza
					WHERE 
						g.id_gracza<>id_player_var AND 
						g.status_online=TRUE AND 
						go.czeka=TRUE AND
						go.id_typ_rozgrywki=id_game_mode_var AND 
						gp.poziom BETWEEN level_enemy_min_var AND level_enemy_max_var;
		
	number_waiting_enemy_var := (SELECT count(*) FROM tmp_table_enemy_var);
	name_enemy_var := (SELECT string_agg(imie, ', ') FROM tmp_table_enemy_var);
	
	--Jesli ilosc graczy jest rozna od wymaganej to wypisz informacje o statusie czekania
	IF number_waiting_enemy_var<>number_waiting_enemy_to_start_game_var THEN
		IF number_waiting_enemy_var > 1 THEN
			RETURN QUERY SELECT FALSE, 3, ('Prosze czekac na odpowiednia liczbe graczy('|| number_waiting_enemy_to_start_game_var::TEXT ||'). Aktualnie czekaja: ' || name_enemy_var || '.')::TEXT, NULL;
			RETURN;
		ELSIF number_waiting_enemy_var > 0 THEN
			RETURN QUERY SELECT FALSE, 3, ('Prosze czekac na odpowiednia liczbe graczy('|| number_waiting_enemy_to_start_game_var::TEXT ||'). Aktualnie czeka: ' || name_enemy_var || '.')::TEXT, NULL;
			RETURN;
		ELSE 
			RETURN QUERY SELECT FALSE, 3, 'Prosze czekac na odpowiednia liczbe graczy('|| number_waiting_enemy_to_start_game_var::TEXT ||'). Aktualnie nikt nie czeka.'::TEXT, NULL;
			RETURN;
		END IF;
	END IF;
	
	--Jesli ilosc graczy jest rowna wymaganej to zainicjuj rozpoczecie rozgrywki   
	IF number_waiting_enemy_var=number_waiting_enemy_to_start_game_var THEN
		
		--pobranie ilosc map
		max_number_maps_var := (SELECT kolejnosc FROM mapy ORDER BY kolejnosc DESC LIMIT 1);
		
		--wylosowanie numeru mapy
		number_drawn_map := (SELECT floor(random()*(max_number_maps_var-2))+1);
		
		--na podstawie numeru mapy pobrac id mapy
		id_drawn_map := (SELECT id_mapy FROM mapy WHERE kolejnosc=number_drawn_map);
		
		--utworzyc nowa bitwe z wylosowana mapa
		INSERT INTO bitwy VALUES(DEFAULT, id_drawn_map, id_game_mode_var, number_waiting_enemy_to_start_game_var + 1) RETURNING id_bitwy INTO id_bitwy_var;
	
		--dodanie do bitwy przeciwnikow gracza
		INSERT INTO bitwy_gracze SELECT NEXTVAL('bitwy_gracze_id_bitwy_gracza_seq'::regclass), id_bitwy_var, id_gracza, NULL, NULL FROM tmp_table_enemy_var;
		
		--dodanie gracza do bitwy
		INSERT INTO bitwy_gracze VALUES(DEFAULT, id_bitwy_var, id_player_var, NULL, NULL);

		--usuniecie tablicy przeciwnikow
		DROP TABLE tmp_table_enemy_var;
		
		--Przestawienie statusu 'czeka' graczom oczekujacym na false, tym ktorzy zostali dodani do rozgrywki
		UPDATE 
			gracze_oczekujacy
		SET 
			czeka=FALSE
		FROM 
		(
			SELECT 
				id_gracza
			FROM
				bitwy_gracze
			WHERE 
				id_bitwy=id_bitwy_var
		) AS bg
		WHERE gracze_oczekujacy.id_gracza=bg.id_gracza;

		--TODO: zamiana potworów oczekujących na pionki
		
		IF number_waiting_enemy_var > 1 THEN
			RETURN QUERY SELECT TRUE, 4, ('Za chwile rozpocznie sie gra z graczami: ' || name_enemy_var || '.')::TEXT, id_bitwy_var;
			RETURN;
		ELSIF number_waiting_enemy_var=1 THEN
			RETURN QUERY SELECT TRUE, 4, ('Za chwile rozpocznie sie gra z graczem: ' || name_enemy_var || '.')::TEXT, id_bitwy_var;
			RETURN;
		END IF;
	END IF;
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_battle_map_for_init(id_player_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT,
	map_ret BYTEA,
	zywiol_ret INT
)  
AS $$
BEGIN

	--czy gracz jest w tabeli 'gracze_oczekujacy'
	IF NOT EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var) THEN
		RETURN QUERY SELECT FALSE, 1, 'Brak oczekujacego gracza o podanym identyfikatorze.'::TEXT, NULL::BYTEA, NULL::INT;
		RETURN;
	END IF;
	
	--Czy gracz jest podczas rozgrywki (musi spelniac warunki: nie czekac i byc w bitwie, ktora nie ma wyniku)
	IF NOT EXISTS(SELECT 1 FROM gracze_oczekujacy WHERE id_gracza=id_player_var AND czeka=FALSE) OR NOT EXISTS(SELECT 1 FROM bitwy_gracze WHERE id_gracza=id_player_var AND id_typ_wyniku_bitwy IS NULL) THEN
		RETURN QUERY SELECT FALSE, 2, 'Nie ma utworzonej bitwy dla danego gracza.'::TEXT, NULL::BYTEA, NULL::INT;
		RETURN;
	END IF;
	
	RETURN QUERY SELECT 
		TRUE, 3, 'OK'::TEXT, m.plik_mapy, m.id_zywiolu 
	FROM 
		mapy m 
		INNER JOIN bitwy b ON b.id_mapy=m.id_mapy
		INNER JOIN bitwy_gracze bg ON bg.id_bitwy=b.id_bitwy 
	WHERE 
		bg.id_typ_wyniku_bitwy IS NULL AND bg.id_gracza=id_player_var; 
		
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_battle_pawn_for_init(id_player_var BIGINT) RETURNS 
TABLE
(
	id_gracz_potwor_ret BIGINT,
	nazwa_ret TEXT,
	opis_ret TEXT,
	tekstura_ret BYTEA,
	zdrowie_ret INT,
	ochrona_ret INT,
	atak_ret INT,
	punkty_ruchu_ret INT,
	pozycja_x_ret INT, 
	pozycja_y_ret INT,
	zywiol_ret INT,
	wrog_ret BOOLEAN
)  
AS $$
BEGIN
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION new_turn(id_player_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE
	id_bitwy_var BIGINT;
	id_gracz_potwor_var BIGINT;
	tura_var INT;
BEGIN
	
	id_bitwy_var := (SELECT id_bitwy FROM bitwy_gracze WHERE id_gracza = id_player_var AND id_typ_wyniku_bitwy IS NULL);
	
	id_gracz_potwor_var := (SELECT id_gracz_potwor FROM gracze_potwory WHERE id_gracza = id_player_var LIMIT 1);
	
	tura_var := (SELECT tura + 1 FROM aktualne_rozgrywki WHERE id_bitwy = id_bitwy_var ORDER BY tura ASC);
	
	--Dodanie nowej tury do rozgrywki w ktorej jest podany gracz
	INSERT INTO aktualne_rozgrywki VALUES(DEFAULT, id_bitwy_var, id_gracz_potwor_var, NULL, 4, NULL, NULL, NULL, NULL, tura_var);
	
	INSERT INTO rozgrywki_log VALUES(DEFAULT, id_bitwy_var, id_gracz_potwor_var, NULL, 4, NULL, NULL, NULL, NULL, tura_var);
	
	--Przywrocenie wszystkim pionkom gracza maksymalna ilosc punktow ruchu
	UPDATE 
		aktualne_rozgrywki
	SET 
		punkty_ruchu = (SELECT gp.punkty_ruchu FROM gracze_potwory AS gp WHERE gp.id_gracz_potwor = id_gracz_potwor)
	WHERE 
		id_bitwy = id_bitwy_var AND
		id_gracz_potwor IN (SELECT gp.id_gracz_potwor FROM gracze_potwory AS gp WHERE gp.id_gracza = id_player_var);
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION move_to_point(id_gracz_potwor_var BIGINT, pozycja_x_var INT, pozycja_y_var INT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE
	punkty_ruchu_var INT;
	zdrowie_var INT;
BEGIN
	
	SELECT punkty_ruchu, zdrowie INTO punkty_ruchu_var, zdrowie_var FROM aktualne_rozgrywki WHERE id_gracz_potwor = id_gracz_potwor_var;
	
	IF punkty_ruchu_var < 1 OR zdrowie_var < 1 THEN
		RETURN QUERY SELECT FALSE, 1, 'Pionek nie moze zostac poruszony.'::TEXT;
		RETURN;
	END IF;

	UPDATE 
		aktualne_rozgrywki 
	SET 
		id_nazwy_czynnosci=2,
		punkty_ruchu = punkty_ruchu - 1,
		pozycja_x = pozycja_x_var,
		pozycja_y = pozycja_y_var
	WHERE 
		id_gracz_potwor = id_gracz_potwor_var;
	
	INSERT INTO rozgrywki_log SELECT nextval('rozgrywki_log_id_rozgrywki_log_seq'::regclass), id_bitwy, id_gracz_potwor, id_zywiolu, id_nazwy_czynnosci, zdrowie, punkty_ruchu, pozycja_x, pozycja_y, tura FROM aktualne_rozgrywki WHERE id_gracz_potwor = id_gracz_potwor_var;
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION attack(id_gracz_potwor_var BIGINT, id_wrog_potwor_var BIGINT, damage INT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN
	
	
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_info_about_enemy_pawn(id_player_var BIGINT) RETURNS 
TABLE
(
	id_gracz_potwor_ret BIGINT,
	zdrowie_ret INT,
	ochrona_ret INT,
	punkty_ruchu_ret INT,
	pozycja_x_ret INT, 
	pozycja_y_ret INT
)  
AS $$
BEGIN
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_new_creature(id_metody_poruszania_potwora_var INT, nazwa_var VARCHAR(50), opis_var TEXT, texture_var BYTEA, zdrowie_var INT, ochrona_var INT, atak_var INT, punkty_ruchu_var INT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN
	
	INSERT INTO potwory VALUES(DEFAULT, id_metody_poruszania_potwora_var, nazwa_var, opis_var, texture_var, zdrowie_var, ochrona_var, atak_var, punkty_ruchu_var);
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_new_map(id_zywiolu_var INT, nazwa_var VARCHAR(50), opis_var TEXT, plik_mapy_var BYTEA) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE
	kolejnosc_var BIGINT;
BEGIN
	
	kolejnosc_var := (SELECT kolejnosc FROM mapy ORDER BY kolejnosc DESC LIMIT 1);
	
	IF kolejnosc_var IS NULL OR kolejnosc_var < 1 THEN
		kolejnosc_var := 0;
	END IF;
	
	kolejnosc_var := kolejnosc_var + 1;
	
	INSERT INTO mapy VALUES(DEFAULT, id_zywiolu_var, nazwa_var, opis_var, plik_mapy_var, kolejnosc_var);
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION registration_player(imie_var VARCHAR(50), nazwisko_var VARCHAR(50), email_var VARCHAR(70), haslo_var VARCHAR(30)) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
DECLARE
	id_garcza_var BIGINT;
BEGIN
	
	IF email_var !~ '^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$' THEN
	RETURN QUERY SELECT FALSE, 1, 'Podany e-mail jest nieprawidlowy.'::TEXT;
		RETURN;
	END IF;
	
	IF EXISTS(SELECT 1 FROM gracze WHERE lower(email) = lower(email_var) AND aktywny=TRUE) THEN
		RETURN QUERY SELECT FALSE, 2, 'Gracz o podanym e-mail istnieje.'::TEXT;
		RETURN;
	END IF;
	
	INSERT INTO gracze VALUES(DEFAULT, imie_var, nazwisko_var, lower(email_var), haslo_var, DEFAULT, DEFAULT, DEFAULT) RETURNING id_gracza INTO id_garcza_var;
	
	INSERT INTO gracze_poziomy VALUES(DEFAULT, id_garcza_var, 1, 0, 500, 3);
	
	INSERT INTO gracze_potwory
		SELECT nextval('gracze_potwory_id_gracz_potwor_seq'::regclass), id_garcza_var, id_potwora, zdrowie, ochrona, atak, punkty_ruchu FROM potwory LIMIT 3;
	
	RETURN QUERY SELECT TRUE, 3, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION set_ban(id_garcza_var BIGINT, data_od_var DATE, data_do_var DATE) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN
	
	IF EXISTS(SELECT 1 FROM gracze_bany WHERE data_od = data_od_var AND data_do = data_do_var AND aktywny=TRUE) THEN
		RETURN QUERY SELECT FALSE, 1, 'Gracz posiada juz bana na podany termin.'::TEXT;
		RETURN;
	END IF;
	
	INSERT INTO gracze_bany VALUES(DEFAULT, id_garcza_var, data_od_var, data_do_var, DEFAULT);
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION delete_player(id_garcza_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN
	
	UPDATE gracze SET aktywny=FALSE, status_online=FALSE WHERE id_gracza = id_garcza_var;
	
	RETURN QUERY SELECT TRUE, 0, 'OK.'::TEXT;
	
END;
$$  LANGUAGE 'plpgsql';


CREATE OR REPLACE FUNCTION add_new_game(id_player_var BIGINT) RETURNS 
TABLE
(
	was_ok_ret BOOLEAN,
	status_ret INT, 
	message_ret TEXT
)  
AS $$
BEGIN
	
END;
$$  LANGUAGE 'plpgsql';



