rm *.o
echo .o files deleted
echo
g++ -c main.cpp -o main.o
as check_property.s -o check_property.o
as transform_rule1.s -o transform_rule1.o
as transform_rule2.s -o transform_rule2.o
g++ main.o check_property.o transform_rule1.o transform_rule2.o -o program