TEMPLATE = subdirs

SUBDIRS += logic_controler_lib \
           graphic_lib \
           game_app \
		   server_app \
		   administrative_tools \
		   moderator_tools 

game_app.depends += logic_controler_lib
game_app.depends += graphic_lib

server_app.depends = logic_controler_lib

OTHER_FILES += .qmake.conf

