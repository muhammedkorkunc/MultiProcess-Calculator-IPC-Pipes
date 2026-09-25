//  calculator.c
//  Name Surname: MUHAMMED EMİN KORKUNÇ
//  Student_No: 2021221054
//  Mail: muhammedemin.korkunc@stu.fsm.edu.tr
//  Lecture: Operating Systems - Project1


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// cd /Users/muhammedeminkorkunc/Desktop/opsis_proj1_MuhammedEmin_Korkunç_2021221054
//  make
// ./calculator



// Kullanıcıdan işlem ve sayıları almak için yardımcı fonksiyon
void fetchInput(int *x, int *y, char *op) {
    // Kullanıcıdan işlem türünü (toplama, çıkarma, çarpma, bölme) al
    printf("Bir işlem seçin (+, -, *, /): ");
    scanf(" %c", op);
    
    // Kullanıcıdan ilk sayıyı al
    printf("İlk sayıyı girin: ");
    scanf("%d", x);
    
    // Kullanıcıdan ikinci sayıyı al
    printf("İkinci sayıyı girin: ");
    scanf("%d", y);
}

int main() {

    int num1, num2;          // Sayılar

    char operator;           // İşlem türü
    int pipe_arr[2];         // Pipe için dosya tanıtıcıları
    pid_t child_pid;         // Alt süreç PID'si

    // Pipe oluşturuluyor 
    if (pipe(pipe_arr) == -1) {
        perror("Pipe oluşturulamadı"); // Pipe oluşturulamazsa hata mesajı
        exit(EXIT_FAILURE);
    }

    // Kullanıcıdan işlem ve sayıları almak için fonksiyonu çağırıyoruz
    fetchInput(&num1, &num2, &operator);

    // Yeni bir alt süreç (child process) oluşturuluyor
    child_pid = fork(); // Yeni bir süreç oluşturuluyor
    // Alt süreç (child process): İşlemi gerçekleştirir.
    // Ana süreç (parent process): Sonuçları alır ve işleme devam eder.

    // fork() işlemi başarısız olursa hata
    if (child_pid < 0) {
        perror("Fork hatası");
        exit(EXIT_FAILURE);
    }

    // Eğer alt süreç (child process) ise
    if (child_pid == 0) {
        // Alt süreç pipe'ın okuma tarafını kapatır
        close(pipe_arr[0]); // Pipe okuma tarafını kapat

        // Pipe'ı standart çıkışa yönlendiriyoruz (alt süreç sonucu pipe üzerinden gönderecek)
        
        dup2(pipe_arr[1], STDOUT_FILENO); // Pipe'ı standart çıkışa yönlendir
        close(pipe_arr[1]); // Pipe yazma tarafını kapat

        // Sayıları karakter dizisine çeviriyoruz (execl kullanabilmek için)
        char num1_str[12], num2_str[12];
        snprintf(num1_str, sizeof(num1_str), "%d", num1);
        snprintf(num2_str, sizeof(num2_str), "%d", num2);

        // execl:
        // Mevcut süreci belirtilen programla değiştirir.
        // İşlemi gerçekleştiren program, sonucu pipe üzerinden ana sürece gönderir.
        // İşlem türüne göre ilgili programı çalıştırıyoruz

        if (operator == '+') {
            execl("./addition", "addition", num1_str, num2_str, NULL); // Toplama
        } else if (operator == '-') {
            execl("./subtraction", "subtraction", num1_str, num2_str, NULL); // Çıkarma
        } else if (operator == '*') {
            execl("./multiplication", "multiplication", num1_str, num2_str, NULL); // Çarpma
        } else if (operator == '/') {
            execl("./division", "division", num1_str, num2_str, NULL); // Bölme
        } else {
            // Geçersiz işlem girildiğinde hata mesajı
            fprintf(stderr, "Geçersiz işlem\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Ana süreç (parent process)
        // Pipe'ın yazma tarafını kapatıyoruz çünkü yalnızca okumaya ihtiyacımız var
        close(pipe_arr[1]);

        int result;
        // Pipe'dan sonucu okuyoruz
        read(pipe_arr[0], &result, sizeof(result));
        close(pipe_arr[0]); // Okuma tarafını kapat

        // parent bekliyor. alt sürecin bitmesini bekliyoruz
        wait(NULL); 

        // Hesaplama sonucunu ekrana yazdırıyoruz
        printf("Hesaplama sonucu: %d\n", result);

        // Sonucu dosyaya kaydetmek için saver programını başlatıyoruz
        pid_t saver_pid = fork();  //Sonucu dosyaya kaydetmek için yeni bir alt süreç oluşturulur.
        if (saver_pid == 0) { 
            // Sonucu karakter dizisine çeviriyoruz
            char result_str[12];
            snprintf(result_str, sizeof(result_str), "%d", result);
            // Saver programını çalıştırıyoruz
            execl("./saver", "saver", result_str, NULL);
        }

        // Saver programının bitmesini bekliyoruz
        wait(NULL);
    }

    return 0; // Program sonlandırılır
}

// Kullanıcı işlem türü ve sayıları girer.
// Ana süreç bir alt süreç oluşturur.
// Alt süreç işlemi yapar ve sonucu pipe üzerinden gönderir.
// Ana süreç, sonucu pipe'dan alır ve ekrana yazdırır.
// Sonuç bir dosyaya kaydedilir.