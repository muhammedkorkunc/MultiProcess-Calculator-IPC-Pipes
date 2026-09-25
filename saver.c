//  saver.c
//  Name Surname: MUHAMMED EMİN KORKUNÇ
//  Student_No: 2021221054
//  Mail: muhammedemin.korkunc@stu.fsm.edu.tr
//  Lecture: Operating Systems - Project1

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Eğer doğru sayıda argüman verilmemişse, kullanıcıya doğru kullanım formatını göster
    if (argc != 2) {
        fprintf(stderr, "Kullanım: ./saver <sonuç>\n");
        return EXIT_FAILURE; // Hatalı kullanımda programı sonlandır
    }

    // Komut satırından alınan sonucu tam sayıya dönüştür
    int result = atoi(argv[1]);

    // "results.txt" dosyasını aç (a modunda ekleme yaparak)
    FILE *file = fopen("results.txt", "a");

    // Dosya açılırken bir hata oluşursa hata mesajı yazdır
    if (file == NULL) {
        perror("Dosya açılmadı");
        return EXIT_FAILURE; // Dosya açılamazsa programı sonlandır
    }

    // Sonucu dosyaya yaz
    fprintf(file, "Sonuç: %d\n", result);

    // Dosyayı kapat
    fclose(file);

    return EXIT_SUCCESS; // Başarıyla sonlanır
}
