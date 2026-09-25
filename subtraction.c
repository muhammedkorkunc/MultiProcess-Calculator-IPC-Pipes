//  subtraction.c
//  Name Surname: MUHAMMED EMİN KORKUNÇ
//  Student_No: 2021221054
//  Mail: muhammedemin.korkunc@stu.fsm.edu.tr
//  Lecture: Operating Systems - Project1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Eğer doğru sayıda argüman verilmemişse, kullanıcıya hata mesajı göster
    if (argc != 3) {
        fprintf(stderr, "Doğru kullanım: ./subtraction <sayı1> <sayı2>\n");
        return EXIT_FAILURE; // Hatalı kullanımda programı sonlandır
    }

    // Komut satırından alınan argümanları tam sayıya dönüştür
    int num1 = atoi(argv[1]);  // İlk sayıyı al
    int num2 = atoi(argv[2]);  // İkinci sayıyı al

    // Çıkarma işlemini yap
    int difference = num1 - num2;

    // Hesaplanan sonucu standart çıkışa (stdout) yaz
    write(STDOUT_FILENO, &difference, sizeof(difference));

    return EXIT_SUCCESS; // Başarıyla sonlanır
}
