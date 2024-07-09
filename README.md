We achieved almost 2500 data to understand the characteristic of the Li-Po Battery : 
![07_07 Veri Seti](https://github.com/haydardk/Power-Module-v1.0-STM32-with-Test-Graphs/assets/134811972/dcdd2194-3dee-4528-a669-a73057ba6a85)
We logged the data :
[07_07 Veri Seti.xlsx](https://github.com/user-attachments/files/16147931/07_07.Veri.Seti.xlsx)
We convert to Percentage Value to process precisely:
[Uploading Voltaj_Fullness.c…]()
#include <stdio.h>
#include <math.h>

// Fonksiyon
double y(double x) {
    return -3e-08 * pow(x, 3) + 0.0003 * pow(x, 2) - 1.1126 * x + 12500;
}

// T�rev fonksiyonu
double dy_dx(double x) {
    return -9e-08 * pow(x, 2) + 0.0006 * x - 1.1126;
}

// Hedef fonksiyon
double target_function(double x, double target_y) {
    return y(x) - target_y;
}

// Newton-Raphson y�ntemi ile belirli bir y de�eri i�in x'i bulma
double find_x_for_y(double target_y, double initial_guess, double tolerance, int max_iterations) {
    double x = initial_guess;
    int i;
    for ( i = 0; i < max_iterations; ++i) {
        double fx = target_function(x, target_y);
        double dfx = dy_dx(x);
        
        if (dfx == 0) {  // T�rev s�f�rsa b�lme hatas� olur
            printf("T�rev s�f�r oldu, k�k bulunam�yor.\n");
            return NAN;  // Not-a-Number (NaN) d�nd�rme
        }
        
        double x_new = x - fx / dfx;
        
        if (fabs(x_new - x) < tolerance) {  // Belirlenen tolerans aral���nda k�k bulunduysa
            return x_new;
        }
        
        x = x_new;
    }
    
    printf("Maksimum iterasyon say�s�na ula��ld�, k�k bulunamad�.\n");
    return NAN;  // Maksimum iterasyon say�s�na ula��l�rsa NaN d�nd�rme
}

// �rnek kullan�m
int main() {
    double target_y  = 12600;  // Belirli bir y de�eri
    double initial_guess = 0;  // Ba�lang�� tahmini
    double tolerance = 1e-6;   // Tolerans
    int max_iterations = 100;  // Maksimum iterasyon say�s�
    
    double x_value = find_x_for_y(target_y, initial_guess, tolerance, max_iterations);
    
    // EK
    double percentage;
    percentage = 100*(1- (x_value +100)/2455) ;  //2455
    int i;
    for (i=0 ; i<30; i++){
    	double x_value = find_x_for_y(target_y, initial_guess, tolerance, max_iterations);
    	percentage = 100*(1- (x_value + 100 )/2455) ;  //2455
    	if (!isnan(x_value)) {
        // printf("Bulunan x de�eri: %lf\n", x_value);
        printf("%.lf %lf\n", target_y , percentage); //Bulunan Voltaj ve  yuzde de�eri: 
        target_y = target_y - 50;
    }
	}
    /* if (!isnan(x_value)) {
        printf("Bulunan x de�eri: %lf\n", x_value);
        printf("Bulunan yuzde de�eri: %lf\n", percentage);
    } */ 
    
    return 0;
}





