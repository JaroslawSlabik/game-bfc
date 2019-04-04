
INCLUDEPATH += $$PWD 

HEADERS += \
	$$PWD/database.h \
    $$PWD/i_query_template.h \
    $$PWD/database_query_gracz_select.h \
    $$PWD/database_query_get_player_creatures.h \
    $$PWD/database_query_get_player_info.h \
    $$PWD/database_query_set_creature_attributes.h \
    $$PWD/database_query_set_insert_creature_waiting.h \
    $$PWD/database_query_set_delete_creature_waiting.h \
    $$PWD/database_query_set_update_creature_waiting.h \
    $$PWD/database_query_set_insert_player_waiting.h \
    $$PWD/database_query_set_abort_waiting.h \
    $$PWD/database_query_get_waiting_info.h \
    $$PWD/database_query_get_battle_map_for_init.h \
    $$PWD/database_query_get_battle_pawn_for_init.h \
    $$PWD/database_query_new_turn.h \
    $$PWD/database_query_move_to_point.h \
    $$PWD/database_query_attack.h \
    $$PWD/database_query_get_info_about_enemy_pawn.h \
    $$PWD/database_query_registration_player.h
	
SOURCES += \
    $$PWD/database.cpp \
    $$PWD/database_query_gracz_select.cpp \
    $$PWD/database_query_get_player_creatures.cpp \
    $$PWD/database_query_get_player_info.cpp \
    $$PWD/database_query_set_creature_attributes.cpp \
    $$PWD/database_query_set_insert_creature_waiting.cpp \
    $$PWD/database_query_set_delete_creature_waiting.cpp \
    $$PWD/database_query_set_update_creature_waiting.cpp \
    $$PWD/database_query_set_insert_player_waiting.cpp \
    $$PWD/database_query_set_abort_waiting.cpp \
    $$PWD/database_query_get_waiting_info.cpp \
    $$PWD/database_query_get_battle_map_for_init.cpp \
    $$PWD/database_query_get_battle_pawn_for_init.cpp \
    $$PWD/database_query_new_turn.cpp \
    $$PWD/database_query_move_to_point.cpp \
    $$PWD/database_query_attack.cpp \
    $$PWD/database_query_get_info_about_enemy_pawn.cpp \
    $$PWD/database_query_registration_player.cpp