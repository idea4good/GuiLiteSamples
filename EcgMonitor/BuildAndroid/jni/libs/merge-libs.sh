echo "Merge libary start..."

ar -x libcore.a
mkdir libcore_objs
mv *.o libcore_objs

ar -x libgui.a
mkdir libgui_objs
mv *.o libgui_objs

ar -x libsample.a
mkdir libsample_objs
mv *.o libsample_objs

ar -r libnative.a libcore_objs/*.o libgui_objs/*.o libsample_objs/*.o

rm -rf libcore_objs libgui_objs libsample_objs
mv libnative.a ../libnative.a
echo "Merge libary done."
