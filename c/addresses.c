#include <stdio.h>


int main() {
    char *s = "HI!";

    printf("%s\n", s);
    printf("%p\n", s); //al poner %p printa la direccion de memoriaa
    
    //tratandolo como array
    printf("%c\n",s[0]); //H
    printf("%c\n",s[1]); //I
    printf("%c\n",s[2]); //!
    printf("%c\n",s[3]); // \0

    printf("%c\n", *s); // Salida -> "H". ya que s es un puntero a la primera letra del string puedo hacer esto
    printf("%c\n", *(s + 1)); //I
    printf("%c\n", *(s + 2)); // !

    printf("%s\n", s); //Hi!
    printf("%02x\n", s); //6945050 valor en hexa

}