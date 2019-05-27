echo "Merge libary start..."

ar -x libGuiLite.a
mkdir libGuiLite_objs
mv *.o libGuiLite_objs

ar -x libUIcode.a
mkdir libUIcode_objs
mv *.o libUIcode_objs

ar -r libnative.a libGuiLite_objs/*.o libUIcode_objs/*.o

rm -rf libGuiLite_objs libUIcode_objs
mv libnative.a ../libnative.a
echo "Merge libary done."
