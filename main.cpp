// Güçlü Parola Analizörü + İki Faktörlü Kimlik Doğrulama (2FA)
// Açıklama: Bu C++ uygulaması güçlü parola kontrolü, güçlü parola oluşturucu, iki faktörlü kimlik doğrulama ve deneme günlüğü içerir.

#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <random>
#include <cstring>


using namespace std;

bool gucluParolaMi(const string& parola) {
    // Güçlü parola kuralları:
    // - En az 8 karakter
    // - En az bir büyük harf
    // - En az bir küçük harf
    // - En az bir rakam
    // - En az bir özel karakter
    regex gucluRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return regex_match(parola, gucluRegex);
}

string gucluParolaOlustur(int uzunluk = 12) {
    const string karakterler = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@$!%*?&";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, karakterler.size() - 1);
    string parola = "";
    for (int i = 0; i < uzunluk; ++i) {
        parola += karakterler[dis(gen)];
    }
    return parola;
}

string ikiFAKoduUret() {
    srand(time(nullptr));
    string kod = "";
    for (int i = 0; i < 6; ++i) {
        kod += to_string(rand() % 10);
    }
    return kod;
}

bool ikiFADogrula(const string& kod) {
    string girilenKod;
    cout << "Cihazınıza gönderilen 2FA kodunu girin: ";
    cin >> girilenKod;
    return girilenKod == kod;
}

void denemeGirdisiYaz(const string& durum) {
    ofstream dosya("gunluk.txt", ios::app);
    time_t simdi = time(0);
    char* zaman = ctime(&simdi);
    zaman[strcspn(zaman, "\n")] = 0; // Yeni satır silinsin
    dosya << "[" << zaman << "] Durum: " << durum << endl;
    dosya.close();
}

int main() {
    cout << "--- Parola Analizörü ve 2FA Sistemi ---" << endl;
    cout << "1. Parola kontrolü\n2. Güçlü parola oluştur\nBir seçenek giriniz: ";

    int secim;
    cin >> secim;

    if (secim == 1) {
        string parola;
        cout << "Parolanızı girin: ";
        cin >> parola;

        if (gucluParolaMi(parola)) {
            cout << "Parola güçlü. 2FA'ya geçiliyor...\n";
            string kod = ikiFAKoduUret();
            cout << "[DEBUG] 2FA kodu: " << kod << endl;

            if (ikiFADogrula(kod)) {
                cout << "Erişim onaylandı.\n";
                denemeGirdisiYaz("Başarılı giriş");
            } else {
                cout << "2FA doğrulama başarısız.\n";
                denemeGirdisiYaz("2FA başarısız");
            }
        } else {
            cout << "Zayıf parola. Lütfen daha güçlü bir parola seçin.\n";
            denemeGirdisiYaz("Zayıf parola");
        }
    } else if (secim == 2) {
        string yeniParola = gucluParolaOlustur();
        cout << "Önerilen güçlü parola: " << yeniParola << endl;
        denemeGirdisiYaz("Güçlü parola oluşturuldu");
    } else {
        cout << "Geçersiz seçenek.\n";
    }

    return 0;
}
