//  multiplication.c
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
        fprintf(stderr, "Doğru kullanım: ./multiplication <sayı1> <sayı2>\n");
        return EXIT_FAILURE; // Hatalı kullanımda programı sonlandır
    }

    // Komut satırından alınan argümanları tam sayıya dönüştür
    int x = atoi(argv[1]);  // İlk sayıyı al
    int y = atoi(argv[2]);  // İkinci sayıyı al

    // Çarpma işlemini yap
    int product = x * y;

    // Hesaplanan sonucu standart çıkışa (stdout) gönder
    write(STDOUT_FILENO, &product, sizeof(product));

    return EXIT_SUCCESS; // Başarıyla sonlanır
}
