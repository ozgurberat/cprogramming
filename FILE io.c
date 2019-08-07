#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1)

/* Type Definitions */
typedef struct date
{
	int day;
	int month;
	int year;
}Date;

typedef struct student
{
	int ID;
	char name[25];
	char surname[25];
	Date birthDate;
	float mathGrade;
	float scienceGrade;
	float trGrade;
}Student;

/* Utility Functions For Students */
Student getStudentFromInput();
void displayStudent(Student);
void displayAllStudents(char*);

/* Student Record Manipulation */
void addStudent(Student);
int deleteStudent(int);
int updateStudent(int);

/* Sorting Functions */
void sortByID(int);
void sortByName(int);
void sortByMathGrade(int);
void sortByScienceGrade(int);
void sortByTrGrade(int);

/* General Utility Functions */
Student* fileToArray(char*);
void arrayToFile(Student*, int, char*);
int getSizeOfClass(char*);
int cmpStrings(char*, char*);
void showMainMenu();

//Change

/* Input Stream'den Ogrenci bilgileri alarak yeni bir Student struct'ý olusturur.
   returns: Olusturulan Student struct'ýný doner.
*/
Student getStudentFromInput(){
	Student st;
	printf("\n********************\n");
	printf("Lutfen Ogrenci Bilgilerini Sirasiyla Giriniz.\n");
	
	printf("Uyari: Dogum tarihini arada / olacak sekilde gg/aa/yyyy formatinda giriniz, gun ve ayda 0 kullanmayiniz.\n");
	
	printf("Ogrenci Numarasi : ");
	scanf("%d", &st.ID);
	
	printf("Adi : ");
	scanf("%s", &st.name);

	printf("Soyadi : ");
	scanf("%s", &st.surname);

	printf("Dogum Tarihi : ");
	scanf("%d/%d/%d", &st.birthDate.day, &st.birthDate.month, &st.birthDate.year);

	printf("Matematik Notu : ");
	scanf("%f", &st.mathGrade);

	printf("Fen Bilgisi Notu : ");
	scanf("%f", &st.scienceGrade);

	printf("Turkce Notu : ");
	scanf("%f", &st.trGrade);
	
	return st;
}

/* Parametre olarak verilen Ogrencinin Bilgilerini Ekrana Basar. */
void displayStudent(Student X){
	
	char no[10], birth[10], mGrade[3],sGrade[3],tGrade[3];
	
	sprintf(no, "%d", X.ID);
	sprintf(birth, "%d/%d/%d", X.birthDate.day,X.birthDate.month,X.birthDate.year);
	sprintf(mGrade, "%.0f", X.mathGrade);
	sprintf(sGrade, "%.0f", X.scienceGrade);
	sprintf(tGrade, "%.0f", X.trGrade);
	
	printf("\n");
	printf("%-10s", no);
	printf("%-20s", X.name);
	printf("%-20s", X.surname);
	printf("%-20s", birth);
	printf("%-20s", mGrade);
	printf("%-20s", sGrade);
	printf("%-20s", tGrade);
}

/* Bütün ogrencilerin bilgilerini ekrana bastirir. */
void displayAllStudents(char* fileName){
	Student st;
	FILE *fp = fopen(fileName,"r+");

	if(fp==NULL)
		printf("Islem Basarisiz.\nHata Nedeni: student.bin dosyasi bulunamadi.\n");
	
	printf("\n");
	printf("%-10s", "No");
	printf("%-20s", "Adi");
	printf("%-20s", "Soyadi");
	printf("%-20s", "Dogum Tarihi");
	printf("%-20s", "Mat. Notu");
	printf("%-20s", "Fen Notu");
	printf("%-20s", "Tr. Notu");
	printf("\n--------------------------------------------------------------------------------------------------------------------\n");

	//Dosya sonunu gorene kadar bloklar halinde ogrenci bilgilerini okur ve ekrana basar	
	while(1){
		fread(&st, sizeof(Student), 1, fp);
		if(feof(fp)) break;
		displayStudent(st);
	}

	fclose(fp);
}

/* Parametre olarak verilen Ogrenci kaydini dosyaya yazar. */
void addStudent(Student st){
	FILE *fp = fopen("student.bin","r+");
	if(fp==NULL) fp=fopen("student.bin","w+");
	fseek(fp, 0, SEEK_END);
	fwrite(&st, sizeof(Student), 1, fp);
	fclose(fp);
	printf("\nOgrenci Kaydi Basarili ile olusturuldu!\n");
}

/* Parametre olarak verilen Ogrenci numarasina sahip ogrenciyi dosyadan siler 
   returns: Dosya acma hatasi veya ogrencinin bulunamamasi durumunda -1 doner. Islem basariliysa silinen ogrenci numarasini doner.
*/
int deleteStudent(int id){
	int i, numberOfRecords, found=0;
	Student st;
	
	FILE *fp = fopen("student.bin", "r+");
	FILE *tmpFile = fopen("tmp.bin", "w+");
	if(fp == NULL || tmpFile == NULL){
		printf("Hata! Dosya acma girisimi basarisiz.\n Program Kapataliyor...");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	numberOfRecords = ftell(fp) / sizeof(Student);
		
	fseek(fp,0,SEEK_SET);
	for(i=0; i<numberOfRecords; i++){
		fread(&st, sizeof(Student), 1, fp);
		if(st.ID != id){
			fwrite(&st, sizeof(Student), 1 , tmpFile);
		}
		else found=1;	
	}
	
	if(found == 0) {
		printf("\n%d numarali ogrenci bulunamadi.", id);
		return -1;
	}
	else printf("\nSilme Islemi Basariyla Tamamlandi...");
	
	fclose(fp);
	fclose(tmpFile);
	
	remove("student.bin");
	rename("tmp.bin", "student.bin");
	return id;
}

/* Parametre olarak verilen Ogrenci numarasina sahip ogrencinin bilgilerini gunceller. 
   returns: Dosya acma hatasi veya ogrencinin bulunamamasi durumunda -1 doner. Islem basariliysa silinen ogrenci numarasini doner.
*/
int updateStudent(int id){
	int i, numberOfRecords, found=0;
	Student st, newSt;
	
	FILE *fp = fopen("student.bin", "r+");
	if(fp == NULL){
		printf("Hata! Dosya acma girisimi basarisiz.\n Program Kapatiliyor...");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	numberOfRecords = ftell(fp) / sizeof(Student);
		
	fseek(fp,0,SEEK_SET);
	for(i=0; i<numberOfRecords; i++){
		fread(&st, sizeof(Student), 1, fp);
		if(st.ID != id){
			continue;
		}
		else{
			found = 1;
			break;
		}	
	}
	
	if(found == 0) {
		printf("\n%d numarali ogrenci bulunamadi.", id);
		return -1;
	}
	else{
		printf("\n%d Numarali Ogrencinin Bilgilerini Simdi Guncelleyebilirsiniz...\n", id);
		newSt = getStudentFromInput();
		fseek(fp, -1*sizeof(Student), SEEK_CUR);
		fwrite(&newSt, sizeof(Student), 1, fp);
		printf("\nGuncelleme Basarili!\n");
	}
	
	fclose(fp);
	
	return id;
}

/*  student.bin dosyasina kayitli ogrencileri numaralarina gore Insertion Sort Algoritmasiyla siralar ve sorted.bin dosyasina kaydeder. */
void sortByID(int size){
	Student* arr = fileToArray("student.bin");
	Student tmpStudent;
	int i, j, key;
	
    for (i = 1; i < size; i++) { 
        key = arr[i].ID;
		tmpStudent = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j].ID > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = tmpStudent; 
    }
	arrayToFile(arr, size, "sorted.bin");
    printf("Ogrenci siralama islemi basariliyla tamamlandi.\nSiralanmis kayitlar sorted.bin dosyasina kaydedildi.");		
}

/*  student.bin dosyasina kayitli ogrencileri isimlerine gore Bubble Sort Algoritmasiyla siralar ve sorted.bin dosyasina kaydeder. */
void sortByName(int size){
	Student* arr = fileToArray("student.bin");
	Student tmpStudent;
	int i, j;

    for (i = 0; i < size-1; i++) {
        for(j=0; j < size - 1 - i; j++){
        	if(cmpStrings(arr[j].name, arr[j+1].name) == 1){
        		tmpStudent = arr[j];
        		arr[j] = arr[j+1];
        		arr[j+1] = tmpStudent;
			}
		}
    }
	arrayToFile(arr, size, "sorted.bin");
	printf("Ogrenci siralama islemi basariliyla tamamlandi.\nSiralanmis kayitlar sorted.bin dosyasina kaydedildi.");	
}

/* student.bin dosyasina kayitli ogrencileri matematik notlarina gore Insertion Sort Algoritmasiyla siralar ve sorted.bin dosyasina kaydeder. */
void sortByMathGrade(int size){
	Student* arr = fileToArray("student.bin");
	Student tmpStudent;
	int i, j, key;
	
    for (i = 1; i < size; i++) { 
        key = arr[i].mathGrade;
		tmpStudent = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j].mathGrade < key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = tmpStudent; 
    }
	arrayToFile(arr, size, "sorted.bin");
    printf("Ogrenci siralama islemi basariliyla tamamlandi.\nSiralanmis kayitlar sorted.bin dosyasina kaydedildi.");			
}

/* student.bin dosyasina kayitli ogrencileri fen notlarina gore Insertion Sort Algoritmasiyla siralar ve sorted.bin dosyasina kaydeder. */
void sortByScienceGrade(int size){
	Student* arr = fileToArray("student.bin");
	Student tmpStudent;
	int i, j, key;
	
    for (i = 1; i < size; i++) { 
        key = arr[i].scienceGrade;
		tmpStudent = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j].scienceGrade < key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = tmpStudent; 
    }
	arrayToFile(arr, size, "sorted.bin");	
	printf("Ogrenci siralama islemi basariliyla tamamlandi.\nSiralanmis kayitlar sorted.bin dosyasina kaydedildi.");	
}

/* student.bin dosyasina kayitli ogrencileri turkce notlarina gore Insertion Sort Algoritmasiyla siralar ve sorted.bin dosyasina kaydeder. */
void sortByTrGrade(int size){
	Student* arr = fileToArray("student.bin");
	Student tmpStudent;
	int i, j, key;
	
    for (i = 1; i < size; i++) { 
        key = arr[i].trGrade;
		tmpStudent = arr[i]; 
        j = i - 1; 
  
        while (j >= 0 && arr[j].trGrade < key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = tmpStudent; 
    }
	arrayToFile(arr, size, "sorted.bin");
	printf("Ogrenci siralama islemi basariliyla tamamlandi.\nSiralanmis kayitlar sorted.bin dosyasina kaydedildi.");	
}

/* Parametre olarak bir Student dizisi ve dizinin boyutunu alir, dizideki elemanlari 3. parametre olan hedef dosya adina yazar. */
void arrayToFile(Student* arr, int size, char* fileName){
	int i;
	FILE *fp = fopen(fileName,"w+");
	if(fp == NULL){
		printf("Hata Meydana Geldi!\nDosya Olusturulamadi..");
	}
	
	fseek(fp, 0, SEEK_SET);
	
	for(i=0; i < size; i++){
		fwrite(&arr[i],sizeof(Student), 1, fp);
	}
	fclose(fp);
}

/* Parametre olarak aldigi dosyadaki Student kayitlarini okur ve dinamik bir diziye aktarir, bu dizinin ilk elemanini gosteren pointeri doner.*/
Student* fileToArray(char* fileName){
	int i, numberOfRecords;
	Student *arr;

	FILE *fp = fopen(fileName, "r+");
	if(fp == NULL){
		printf("Hata! Dosya acma girisimi basarisiz.\n Program Kapatiliyor...");
	}
	fseek(fp,0,SEEK_END);
	numberOfRecords = ftell(fp) / sizeof(Student);
	
	arr = (Student*) malloc(sizeof(Student)*numberOfRecords);
	
	fseek(fp,0,SEEK_SET);
	for(i=0; i<numberOfRecords; i++){
		fread(&arr[i], sizeof(Student), 1, fp);
	}
	return arr;
}

/* Parametre olarak aldigi dosyadaki kayitli Student sayisini bulur ve doner.*/
int getSizeOfClass(char* fileName){
	int size;
	FILE *fp = fopen(fileName,"r+");

	if(fp==NULL)
		printf("Islem Basarisiz.\n");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp) / sizeof(Student);
	fclose(fp);
	return size;
}

/* Parametre olarak aldigi 2 stringi karsilastirir, ilk parametre buyukse 1, Ikinci parametre buyuk veya esitlerse -1 doner. */
int cmpStrings(char* str1, char* str2){
	int i=0;
	while((str1[i] != '\0') || (str2[i] != '\0')){
		if(str1[i] < str2[i]){
			return -1;
		}
		else if(str1[i] > str2[i]){
			return 1;
		}
		else{
			i++;
			continue;
		}	
	}
	return -1;
}

/* Ana Menuyu Gosteren Fonksiyon */
void showMainMenu(){
	int choice, id, size;
	Student st;
	size = getSizeOfClass("student.bin");
	printf("1 - Ogrenci Kaydi Ekle\n");
	printf("2 - Ogrenci Kaydi Sil\n");
	printf("3 - Ogrenci Kaydi Guncelle\n");
	printf("4 - Tum Ogrencileri Listele\n");
	printf("5 - Ogrencileri Numaralarina Gore Sirala\n");
	printf("6 - Ogrencileri Isimlerine Gore Sirala\n");
	printf("7 - Ogrencileri Matematik Notlarina Gore Sirala\n");
	printf("8 - Ogrencileri Fen Bilgisi Notlarina Gore Sirala\n");
	printf("9 - Ogrencileri Turkce Notlarina Gore Sirala\n");
	printf("Lutfen sectiginiz menunun numarasini giriniz: ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:
			st = getStudentFromInput();
			addStudent(st);
			break;
		case 2:
			printf("\n Kaydini Silmek Istediginiz Ogrencinin Numarasini Giriniz: ");
			scanf("%d", &id);
			deleteStudent(id);
			break;
		case 3:
			printf("\n Kaydini Guncellemek Istediginiz Ogrencinin Numarasini Giriniz: ");
			scanf("%d", &id);
			updateStudent(id);
			break;
		case 4:
			displayAllStudents("student.bin");
			break;
		case 5:
			printf("\nOgrenciler Numaralarina Gore Siralaniyor...");
			sortByID(size);
			printf("\nSiralanmis Liste Gosteriliyor...\n");
			displayAllStudents("sorted.bin");
			break;
		case 6:
			printf("\nOgrenciler Isimlerine Gore Siralaniyor...");
			sortByName(size);
			printf("\nSiralanmis Liste Gosteriliyor...\n");
			displayAllStudents("sorted.bin");
			break;
		case 7:
			printf("\nOgrenciler Matematik Notlarina Gore Siralaniyor...");
			sortByMathGrade(size);
			printf("\nSiralanmis Liste Gosteriliyor...\n");
			displayAllStudents("sorted.bin");
			break;
		case 8:
			printf("\nOgrenciler Fen Bilgisi Gore Siralaniyor...");
			sortByScienceGrade(size);
			printf("\nSiralanmis Liste Gosteriliyor...\n");
			displayAllStudents("sorted.bin");
			break;
		case 9:
			printf("\nOgrenciler Turkce Notlarina Gore Siralaniyor...");
			sortByTrGrade(size);
			printf("\nSiralanmis Liste Gosteriliyor...\n");
			displayAllStudents("sorted.bin");
			break;
		default:
			break;	
	}

}

int main(){
	int choice;
	while(1){
		showMainMenu();
		printf("\nBaska Islem Yapmak Istiyorsaniz 1 Yazip Enter Tusuna Basin. Cikmak icin 0 giriniz.\nSeciminiz: ");
		scanf("%d", &choice);
		if(choice == 1){
			printf("\n\n------------------------------------------------------------------\n");
			continue;
		}
		else break;
	}
	return 0;
}

