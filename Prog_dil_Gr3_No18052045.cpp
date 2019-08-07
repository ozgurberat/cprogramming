#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int*, int*);
void printArray(int*, int);
void compareSorts();
void populateRandomArray(int*, int, int);
double selectionSort(int*, int, bool);
double bubbleSort(int*, int, bool);
double insertionSort(int*, int, bool);
double shellSort(int*, int, bool);

/*  Parametre olarak aldigi 2 elemanýn yerlerini degistirir.
*/
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*  Parametre olarak aldigi dizinin elemanlarini yan yana ekrana basar. */
void printArray(int arr[], int n){ 
    for (int i=0; i < n; i++){
        printf("%d ", arr[i]);     
    } 
    printf("\n"); 
} 

/*  Parametre olarak bir tam sayi dizisi, dizinin boyutunu ve elemanlarin alacagi maksimum degeri alir.
    Dizinin tüm elemanlarini [0-rangeMax] araliginda olacak sekilde tesadufsel olarak gunceller. 
*/
void populateRandomArray(int dizi[], int size, int rangeMax){
	srand(time(0)); 
    for(int i=0; i<size; i++){
        dizi[i] = (rand() % rangeMax) + 1;
    }
}

/*  4 Siralama algoritmasini birbiri ile karsilastirir ve calisma surelerini ekrana basar 
*/
void compareSorts(){
    int dizi[50000];

    populateRandomArray(dizi, 50000, 200000);
    printf("Bubble sort %lf saniyede siraladi. \n", bubbleSort(dizi, 50000, true));

    populateRandomArray(dizi, 50000, 200000);
    printf("Selection sort %lf saniyede siraladi. \n", selectionSort(dizi, 50000, true));
    
    populateRandomArray(dizi, 50000, 200000);
    printf("Insertion sort %lf saniyede siraladi. \n", insertionSort(dizi, 50000, true)); 
    
    populateRandomArray(dizi, 50000, 200000);
    printf("Shell sort %lf saniyede siraladi. \n", shellSort(dizi, 50000, true));  
}

/*  Secme siralamasi algoritmasidir.
    incOrder parametresi True ise artan sekilde siralar, aksi taktirde azalan sekilde siralar.
*/
double selectionSort(int arr[], int size, bool incOrder){
    int key, i, j;
    clock_t start, end;
    double cpu_time_used;
     
    start = clock();

    // Artan sekilde sirala
    if(incOrder){
        for(int i=0; i < size; i++){
            key = i;
            for(int j=i; j < size; j++){
                if(arr[j] < arr[key]) key = j;
            }
            swap(&arr[i], &arr[key]);
        }    
    }
    // Azalan sekilde sirala
    else{
        for(int i=0; i < size; i++){
            key = i;
            for(int j=i; j < size; j++){
                if(arr[j] > arr[key]) key = j;
            }
            swap(&arr[i], &arr[key]);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)); // ms
    return cpu_time_used/1000;
}

/*  Kabarcik siralamasi algoritmasidir.
    incOrder parametresi True ise artan sekilde siralar, aksi taktirde azalan sekilde siralar.
*/
double bubbleSort(int arr[], int size, bool incOrder){
    int sorted;
    clock_t start, end;
    double cpu_time_used;
     
    start = clock();
    // Artan sekilde sirala
    if(incOrder){
        for(int i=0; i < size; i++){
            sorted = 1;
            for(int j=0; j<size-i-1; j++ ){
                if(arr[j] > arr[j+1]){
                    swap(&arr[j], &arr[j+1]);
                    sorted = 0;
                }
            }
            if(sorted==1) break;
        }
    }
    // Azalan sekilde sirala
    else{
        for(int i=0; i < size; i++){
            sorted = 1;
            for(int j=0; j<size-i-1; j++ ){
                if(arr[j] < arr[j+1]){
                    swap(&arr[j], &arr[j+1]);
                    sorted = 0;
                }
            }
            if(sorted==1) break;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start));
    return cpu_time_used/1000;
}

/*  Ekleme siralamasi algoritmasidir, 
    incOrder parametresi True ise artan sekilde siralar, aksi taktirde azalan sekilde siralar.
*/
double insertionSort(int arr[], int size, bool incOrder){
    clock_t start, end;
    double cpu_time_used;
     
    start = clock();
    // Artan sekilde sirala
    if(incOrder){
        for(int i=1; i < size; i++){
            for(int j=i; j>0 && (arr[j] < arr[j-1]); j--){
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
    // Azalan sekilde sirala
    else{
        for(int i=1; i < size; i++){
            for(int j=i; j>0 && (arr[j] > arr[j-1]); j--){
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start));
    return cpu_time_used/1000;
}

/*  Shell sýralamasý algoritmasidir.
    incOrder parametresi True ise artan sekilde siralar, aksi taktirde azalan sekilde siralar.
*/
double shellSort(int arr[], int size, bool incOrder){
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    // Artan sekilde sirala
    if(incOrder){
        for(int h = size/2; h>=1; h /= 2){
            for(int i=h; i < size; i++){
                for(int j=i; j>=h && arr[j] < arr[j-h]; j-=h){
                    swap(&arr[j], &arr[j-h]);
                }
            }
        } 
    }
    // Azalan sekilde sirala
    else{
        for(int h = size/2; h>=1; h /= 2){
            for(int i=h; i < size; i++){
                for(int j=i; j>=h && arr[j] > arr[j-h]; j-=h){
                    swap(&arr[j], &arr[j-h]);
                }
            }
        }                 
    }
    end = clock();
    cpu_time_used = ((double) (end - start));
    return cpu_time_used/1000;
}

int main(){
    char menu1, menu1_A, menu1_A_KB; // Menu secimlerini tutan degiskenler
    bool incOrder = false;
    
    // Ilk Menu Ekrani, A ya da B secimi yapilabilir.
    printf("==================== MENU ====================\n");
    printf("A) Bir siralama algoritmasi secerek diziyi siralayiniz.\n");
    printf("B) Tum siralama algoritmalarini karsilastiriniz.\n");
    scanf(" %c", &menu1);
    
    // Eðer B secimi yapilirsa siralama algoritmalarini karsilastiran fonksiyonu cagirir.
    if(menu1 == 'B' || menu1 == 'b'){
        compareSorts();
    }
    // Eger A secimi yapilirsa bir alt menuye gecer.
    else if(menu1 == 'A' || menu1 == 'a'){
        // Siralama algoritmasi ve siralama sekli secilmesi istenen alt menuler
        printf("Siralama Algoritmasi Seciniz: .\n");
        printf("\t1. Bubble Sort (Kabarcik Siralamasi).\n");
        printf("\t2. Selection Sort (Secme Siralamasi).\n");
        printf("\t3. Insertion Sort (Ekleme Siralamasi).\n");
        printf("\t4. Shell Sort (Shell Siralamasi).\n");
        scanf(" %c", &menu1_A);
        
        printf("Siralama Sekli:\n");
        printf("\t1. Kucukten Buyuge\n");
        printf("\t2. Buyukten Kucuge\n");
        scanf(" %c", &menu1_A_KB);
        if(menu1_A_KB != '1' && menu1_A_KB != '2'){ printf("Hatali secim yaptiniz. Programi tekrar calistirin..\n"); return 0; }
        
        if(menu1_A_KB == '1') incOrder = true;
        // Su ana kadar hangi algoritmanin kullanilacagi ve siralanis tipi degiskenlere atandi.
        // 10 elemanli bir dizi olusturup, [1-100] arasi rastgele elemanlarla icini doldurur.
        int dizi[10];
        populateRandomArray(dizi, 10, 100);

        // Rastgele elemanlar atandýktan sonra ekrana önce sýralanmamýþ halini basar.
        printf("Dizinin Siralanmamis Hali -> ");
        printArray(dizi,10);

        // Menu secimi icin switch-case yapisi kullanilmistir. 
        // Kullanicinin girdigi menu numarasina gore siralama islemi yapilir. 
        // Her siralama algoritmasi siralama yonunu parametre olarak alir.
        switch(menu1_A){
            case '1':
                bubbleSort(dizi, 10, incOrder);
                break;
            case '2':
                selectionSort(dizi, 10, incOrder);
                break;
            case '3':
                insertionSort(dizi, 10, incOrder);
                break;
            case '4':
                shellSort(dizi, 10, incOrder);
                break;
            default: printf("Yanlis bir secim yaptiniz. Seciminiz 1-4 araliginda olmalidir, programi tekrar calistirin.");
                break;
        }

        // Dizinin siralandiktan sonraki hali ekrana basilir.
        printf("Dizinin Siralanmis Hali -> ");
        printArray(dizi,10);
    }

    // A ya da B menuleri secilmediyse yanlis bir tusa basilmis demektir. Hata mesaji verir.
    else{
        printf("Yanlis menu secimi yaptiniz. Lutfen kucuk-buyuk harf fark etmezsizin A ya da B menulerinden birini secin.");
    }
} 
