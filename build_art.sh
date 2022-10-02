echo "#ifndef _ART_H_" > src/art.h
echo "#define _ART_H_" >> src/art.h
echo "" >> src/art.h
w4 png2src --c art-src/sprite_enemy.png >> src/art.h
echo "#endif" >> src/art.h

echo "#ifndef _ARTMENU_H_" > src/artmenu.h
echo "#define _ARTMENU_H_" >> src/artmenu.h
echo "" >> src/artmenu.h
w4 png2src --c art-src/spacelord.png >> src/artmenu.h
echo "#endif" >> src/artmenu.h
