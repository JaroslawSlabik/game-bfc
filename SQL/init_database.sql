CREATE TABLE wersja_bazy
(
	major INT NOT NULL,
	minior INT NOT NULL,
	bug_fix INT NOT NULL
);
INSERT INTO wersja_bazy VALUES(1,0,0);

CREATE TABLE gracze
(
	id_gracza BIGSERIAL PRIMARY KEY,
	imie VARCHAR(50) NOT NULL,
	nazwisko VARCHAR(50) NOT NULL,
	email VARCHAR(70) NOT NULL,
	haslo VARCHAR(30) NOT NULL,
	data_dolaczenia DATE NOT NULL DEFAULT NOW(),
	aktywny BOOLEAN NOT NULL DEFAULT TRUE,
	status_online BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE TABLE gracze_poziomy
(
	id_gracza_poziom BIGSERIAL PRIMARY KEY,
	id_gracza BIGINT NOT NULL UNIQUE REFERENCES gracze(id_gracza),
	poziom INT NOT NULL,
	doswiadczenie BIGINT NOT NULL,
	doswiadczenie_nastepny_poziom BIGINT NOT NULL,
	punkty_do_rozdania INT NOT NULL
);

CREATE TABLE gracze_bany
(
	id_gracza_ban BIGSERIAL PRIMARY KEY,
	id_gracza BIGINT REFERENCES gracze(id_gracza),
	data_od DATE NOT NULL DEFAULT NOW(),
	data_do DATE NOT NULL,
	aktywny BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE TABLE typy_rozgrywki
(
	id_typ_rozgrywki INT PRIMARY KEY,
	nazwa VARCHAR(40) NOT NULL,
	liczba_wymaganych_przeciwnikow INT NOT NULL
);
INSERT INTO typy_rozgrywki VALUES	(1, '1 Gracz VS 1 Gracz', 1),
									(2, '2 Graczy VS 2 Graczy', 3),
									(3, '1 Gracz VS CPU', 99);

CREATE TABLE metody_poruszania_potwora
(
	id_metody_poruszania_potwora INT PRIMARY KEY,
	nazwa VARCHAR(50) NOT NULL
);
INSERT INTO metody_poruszania_potwora VALUES(1, 'Chodzi po ziemi'),
											 (2, 'Lata w powietrzu');

CREATE TABLE potwory
(
	id_potwora BIGSERIAL PRIMARY KEY,
	id_metody_poruszania_potwora INT REFERENCES  metody_poruszania_potwora(id_metody_poruszania_potwora),
	nazwa VARCHAR(50) NOT NULL,
	opis TEXT,
	texture BYTEA, 
	zdrowie INT NOT NULL,
	ochrona INT NOT NULL,
	atak INT NOT NULL,
	punkty_ruchu INT NOT NULL
);

CREATE TABLE gracze_potwory
(
	id_gracz_potwor BIGSERIAL PRIMARY KEY,
	id_gracza BIGINT REFERENCES gracze(id_gracza),
	id_potwora BIGINT REFERENCES potwory(id_potwora),  
	zdrowie INT NOT NULL,
	ochrona INT NOT NULL,
	atak INT NOT NULL,
	punkty_ruchu INT NOT NULL
);

CREATE TABLE gracze_oczekujacy
(
	id_gracza_oczekujacego BIGSERIAL PRIMARY KEY,
	id_gracza BIGINT REFERENCES gracze(id_gracza),
	id_typ_rozgrywki INT REFERENCES typy_rozgrywki(id_typ_rozgrywki),
	data_utworzenia TIMESTAMP DEFAULT NOW(),
	czeka BOOLEAN DEFAULT TRUE,
	data_modyfikacji TIMESTAMP DEFAULT NOW()
);

CREATE TABLE zywioly
(
	id_zywiolu INT PRIMARY KEY,
	nazwa VARCHAR(50) NOT NULL,
	opis TEXT NOT NULL
);
INSERT INTO zywioly VALUES	(1, 'Ogien', 'Zywiol ogień'),
						(2, 'Woda', 'Zywiol woda'),
						(3, 'Powietrze', 'Zywiol powietrze'),
						(4, 'Ziemia', 'Zywiol ziemia');

CREATE TABLE zywioly_relacje
(
	id_zywiol_relacja SERIAL PRIMARY KEY,
	id_zywiolu_1 INT REFERENCES zywioly(id_zywiolu),
	id_zywiolu_2 INT REFERENCES zywioly(id_zywiolu),
	mnoznik REAL NOT NULL
);
INSERT INTO zywioly_relacje VALUES (DEFAULT, 1, 1, 1.0),
								(DEFAULT, 1, 2, 1.0),
								(DEFAULT, 1, 3, 1.0),
								(DEFAULT, 1, 4, 1.0),
								(DEFAULT, 2, 1, 1.0),
								(DEFAULT, 2, 2, 1.0),
								(DEFAULT, 2, 3, 1.0),
								(DEFAULT, 2, 4, 1.0),
								(DEFAULT, 3, 1, 1.0),
								(DEFAULT, 3, 2, 1.0),
								(DEFAULT, 3, 3, 1.0),
								(DEFAULT, 3, 4, 1.0),
								(DEFAULT, 4, 1, 1.0),
								(DEFAULT, 4, 2, 1.0),
								(DEFAULT, 4, 3, 1.0),
								(DEFAULT, 4, 4, 1.0);
					
CREATE TABLE potwory_graczy_oczekujacych
(
	id_potwora_gracza_oczekujacego BIGSERIAL PRIMARY KEY,
	id_gracza_oczekujacego BIGINT REFERENCES gracze_oczekujacy(id_gracza_oczekujacego),
	id_gracz_potwor BIGINT REFERENCES gracze_potwory(id_gracz_potwor),
	id_zywiolu INT REFERENCES zywioly(id_zywiolu),
	pozycja_x INT NOT NULL,
	pozycja_y INT NOT NULL
);

CREATE TABLE mapy
(
	id_mapy BIGSERIAL PRIMARY KEY,
	id_zywiolu INT REFERENCES zywioly(id_zywiolu),
	nazwa VARCHAR(50) NOT NULL,
	opis TEXT NOT NULL,
	plik_mapy BYTEA NOT NULL,
	kolejnosc BIGINT NOT NULL
);

CREATE TABLE mapy_pozycje_pol
(
	id_mapy_pozycje_pol BIGSERIAL PRIMARY KEY,
	id_mapy BIGINT NOT NULL REFERENCES mapy(id_mapy),
	numer_pola INTEGER NOT NULL,
	pozycja_x_pola INTEGER NOT NULL,
	pozycja_y_pola INTEGER NOT NULL,
	pozycja_x_mapy INTEGER NOT NULL,
	pozycja_y_mapy INTEGER NOT NULL
);

CREATE TABLE bitwy
(
	id_bitwy BIGSERIAL PRIMARY KEY,
	id_mapy BIGINT REFERENCES mapy(id_mapy),
	id_typ_rozgrywki INT REFERENCES typy_rozgrywki(id_typ_rozgrywki),
	liczba_graczy INT NOT NULL
);
	
	--TODO: zapisanie do rozgrywki_log
CREATE TABLE typy_wynikow_bitwy
(
	id_typ_wyniku_bitwy INT PRIMARY KEY,
	nazwa VARCHAR(50) NOT NULL
);
INSERT INTO typy_wynikow_bitwy VALUES(1, 'Wygrana'),
									 (2, 'Przegrana'),
									 (3, 'Remis'),
									 (4, 'Rezygnacja');

CREATE TABLE bitwy_gracze
(
	id_bitwy_gracza BIGSERIAL PRIMARY KEY,
	id_bitwy BIGINT REFERENCES bitwy(id_bitwy),
	id_gracza BIGINT REFERENCES gracze(id_gracza),
	id_typ_wyniku_bitwy INT REFERENCES typy_wynikow_bitwy(id_typ_wyniku_bitwy),
	punkty_zdobyte INT NOT NULL
);

CREATE TABLE nazwy_czynnosci
(
	id_nazwy_czynnosci INT PRIMARY KEY,
	nazwa VARCHAR(50) NOT NULL
);
INSERT INTO nazwy_czynnosci VALUES(1, 'Rozpoczecie rozgrywki'),
								  (2, 'Poruszenie pionkiem'),
								  (3, 'Zaatakowanie przeciwnika'),
								  (4, 'Nastepna tura'),
								  (5, 'Zakonczenie rozgrywki');

CREATE TABLE aktualne_rozgrywki
(
	id_aktualnej_rozgrywki BIGSERIAL PRIMARY KEY,
	id_bitwy BIGINT REFERENCES bitwy(id_bitwy),
	id_gracz_potwor BIGINT REFERENCES gracze_potwory(id_gracz_potwor),
	id_zywiolu INT REFERENCES zywioly(id_zywiolu),
	id_nazwy_czynnosci INT REFERENCES nazwy_czynnosci(id_nazwy_czynnosci),
	zdrowie INT NOT NULL,
	punkty_ruchu INT NOT NULL,
	pozycja_x INT NOT NULL,
	pozycja_y INT NOT NULL,
	tura INT NOT NULL
);

CREATE TABLE rozgrywki_log
(
	id_rozgrywki_log BIGSERIAL PRIMARY KEY,
	id_bitwy BIGINT REFERENCES bitwy(id_bitwy),
	id_gracz_potwor BIGINT REFERENCES gracze_potwory(id_gracz_potwor),
	id_zywiolu INT REFERENCES zywioly(id_zywiolu),
	id_nazwy_czynnosci INT REFERENCES nazwy_czynnosci(id_nazwy_czynnosci),
	zdrowie INT NOT NULL,
	punkty_ruchu INT NOT NULL,
	pozycja_x INT NOT NULL,
	pozycja_y INT NOT NULL,
	tura INT NOT NULL
);

CREATE TABLE konfiguracja_systemu
(
	nazwa VARCHAR(100) PRIMARY KEY,
	opis TEXT,
	wartosc VARCHAR(100)
);
