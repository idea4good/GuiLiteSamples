echo "Merge libary start..."

ar -x libcore.a
mkdir libcore_objs
mv *.o libcore_objs

ar -x libgui.a
mkdir libgui_objs
mv *.o libgui_objs

ar -x libUIcode.a
mkdir libUIcode_objs
mv *.o libUIcode_objs

ar -r libnative.a libcore_objs/*.o libgui_objs/*.o libUIcode_objs/*.o

rm -rf libcore_objs libgui_objs libUIcode_objs
mv libnative.a ../libnative.a
echo "Merge libary done."
