//  addition.c
//  Name Surname: MUHAMMED EMİN KORKUNÇ
//  Student_No: 2021221054
//  Mail: muhammedemin.korkunc@stu.fsm.edu.tr
//  Lecture: Operating Systems - Project1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// argc: Komut satırından gelen argüman sayısını tutar.
// argv: Komut satırından gelen argümanların dizisidir.
// argv[0]: Programın adı (./addition).
// argv[1] ve argv[2]: Kullanıcı tarafından girilen iki sayı.

int main(int argc, char *argv[]) {
    // Eğer doğru sayıda argüman verilmemişse, kullanıcıya hata mesajı göster
    if (argc != 3) { 
        fprintf(stderr, "Doğru kullanım: ./addition <sayı1> <sayı2>\n"); //stderr: Standart hata çıkışı
        return EXIT_FAILURE; // Hatalı kullanımda programı sonlandır
    }

    // Verilen string argümanları tam sayıya dönüştür atoi (ASCII to Integer)
    int a = atoi(argv[1]);  // İlk sayıyı al
    int b = atoi(argv[2]);  // İkinci sayıyı al
    
    // Toplama işlemini yap
    int result = a + b;

    // Hesaplanan sonucu standart çıkışa (stdout) gönder
    write(STDOUT_FILENO, &result, sizeof(result)); 
    //STDOUT_FILENO sonucu parent process göndermemizi sağlar.

    return EXIT_SUCCESS; // Başarılı bir şekilde sonlanır
}
