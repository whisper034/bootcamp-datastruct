#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef long long int ll;

void title();
void displayPurchased(struct data purchased[], ll totalPurchased);
void displayAvailable(ll size);
void customerFile(struct data purchased[], char temp1[], char name[], ll totalPurchased, ll total, int persen, ll diskon, ll result);

struct data {
	char code[10];
	char barang[100];
	ll quantity;
	ll price;
};

struct data data1[1000]; // inisialisasi struct di luar main() biar masuk ke function displayAvailable() di paling bawah

int main() {
	title();
	FILE *ptr;
	ptr = fopen("data.txt", "r");
	
	printf("Searching the file(s) required"); sleep(1); printf("."); sleep(1); printf("."); sleep(1); printf("."); sleep(2); puts("");
	if(ptr == NULL) puts("File 'data.txt' not found.");
	else printf("Succesfully located 'data.txt'."); sleep(2);
	system("cls");
	
	// program untuk menghitung ada berapa line/row/baris di dalam file
	title();
	char c;
	int record = 0;
	for(c = getc(ptr); c != EOF; c = getc(ptr)) {
        if (c == '\n') record++; 
    }
    ll size = record + 1;
//    printf("%d\n", size);
	
	// langsung close file, akan terjadi error/bug yang aneh (di laptop saya)
	fclose(ptr);
	
	// Pembatas aja
	
	// buat pembuka file baru
	FILE *fp;
	fp = fopen("data.txt", "r");
	
	for(int i = 0; i < size; i++) {
		fscanf(fp, "%[^#]#%[^#]#%lld#%lld\n", data1[i].code, data1[i].barang, &data1[i].quantity, &data1[i].price);
	}
	printf("Scanning file(s)"); sleep(1); printf("."); sleep(1); printf("."); sleep(1); printf("."); sleep(2); puts("");
	system("cls");
	
	// display stok yang tersedia
	title();
	displayAvailable(size);
	system("pause");
	system("cls");
	
	title();
	ll empty = 0;
	for(int i = 0; i < size; i++) {
		if(data1[i].quantity == 0) empty++;
	}
	
	// bila SEMUA produk habis
	if(empty == size) {
		puts("All products are out of stocks!");
		puts("Please restock immediately!");
		exit(0); // langsung exit aja
	}
	
	// bila at least 1 produk belum habis lanjut sini
	char temp[100], name[100];
	ll newSales = 0; // sebagai tanda untuk NEW CUSTOMER
	while(newSales == 0) {
		system("cls");
		title();
		empty = 0;
		for(int i = 0; i < size; i++) {
			if(data1[i].quantity == 0) empty++;
		}
		
		// bila SEMUA produknya habis, langsung update stoknya, intinya langsung ke menu/option 3
		if(empty == size) {
			FILE *update;
			update = fopen("data.txt", "w");
			for(int i = 0 ; i < size; i++) {
				if(i == size - 1) fprintf(update, "%s#%s#%lld#%lld", data1[i].code, data1[i].barang, data1[i].quantity, data1[i].price);
				else fprintf(update, "%s#%s#%lld#%lld\n", data1[i].code, data1[i].barang, data1[i].quantity, data1[i].price);
			}
			fclose(update);
			puts("All products are out of stocks!");
			puts("Please restock immediately!");
			exit(0);
		}
		
		// bila at least 1 produk masih ada, lanjut sini
		printf("Dear customer, please humbly tell us your name:\nName: ");
		scanf("%[^\n]", temp); getchar();
		
		// bila jumlah char kurang dari 5 atau lebih dari 30
		while(strlen(temp) < 5 || strlen(temp) > 30) {
	      system("cls");
	      title();
			puts("Dear customer, the name should be around 5 - 30 characters.");
	      printf("Name: ");
	      scanf("%[^\n]", temp); getchar();
	    }
		strcpy(name, temp);
		printf("\nHello, %s!\n\n", name);
		newSales = 1; // biar ngga ngulang minta nama lagi
		system("pause");
		
		// inisialisasi struct purchased setelah input nama customer, agar setiap new customer, index array struct akan ke-reset
		struct data purchased[1000];
		
		ll total = 0; // harga total
		ll countIndex = 0; // countIndex untuk data barang yang dibeli customer
		ll totalPurchased = 0; // berapa kali customer membeli barang
		int done = 0; // sebagai tanda apakah programnya sudah selesai atau belum
		while(done == 0) {
			system("cls");
			title();
			puts("What do you want to do?");
			puts("1. Input Sales");
			puts("2. Finish Sales");
			puts("3. Exit");
			
			int choose;
			printf("\nAnswer: ");
			scanf("%d", &choose); getchar();
			
			// bila meng-input tidak sesuai dengan pilihan yang ada
			while(choose < 1 || choose > 3) {
				system("cls");
				title();
				puts("Please input the correct number."); sleep(2);
				puts("1. Input Sales");
				puts("2. Finish Sales");
				puts("3. Exit");
				printf("\nAnswer: ");
				scanf("%d", &choose); getchar();
			}
			
			system("cls");
			title();
			switch(choose) {
				// Input Sales
				case 1: {
					empty = 0;
					for(int i = 0; i < size; i++) {
						if(data1[i].quantity == 0) empty++;
					}
					// bila SEMUA produk habis, akan diminta untuk langsung ke menu/option 2
					if(empty == size) {
						puts("All products are out of stocks!"); sleep(2);
						puts("Please go to option 2: Finish Sales immediately..."); sleep(2);
						system("pause");
						break;
					}
					
					// bila at least masih ada 1 produk tersedia, lanjut sini
					char temp[10];
					printf("Input Product's Code: "); // input kode produk
					scanf("%s", temp); getchar();
					puts("");
					ll index;
					int found;
					for(int i = 0; i < size; i++) {
						found = strcmp(temp, data1[i].code);
						if(found == 0) { // bila produknya ketemu
							index = i; // set index untuk kode produk yang ditemukan
							break; // langsung break aja, karena setiap kode produk pasti berbeda
								   // bila tidak di-break, akan jadi error.
						}
					}
					
					// bila produknya ngga ketemu
					if(found != 0) {
						puts("Product not found.");
						break;
					}
					
					// bila produknya ketemu, lanjut sini
					else if(found == 0) {
						// bila produk yang diinginkan dan masih ada stoknya, lanjut sini
						if(data1[index].quantity != 0) {
							ll purchase;
							printf("Total stock(s) for %s: %lld\n", data1[index].barang, data1[index].quantity);
							printf("Price of %s: %lld\n", data1[index].barang, data1[index].price); sleep(1);
							printf("\nHow many do you want to purchase?\nInput: ");
							scanf("%lld", &purchase); getchar();
							
							// minimal pembelian 1 buah dan maksimal pembelian sesuai kuantitas yang tersedia
							while(purchase < 1 || purchase > data1[index].quantity) {
								// bila pembelian kurang dari 1
								if(purchase < 1) {
									system("cls");
									title();
									puts("Please make a minimum purchase of 1.");
								}
								
								// bila pembelian lebih dari kuantitas/stok yang tersedia
								else if(purchase > data1[index].quantity) {
									system("cls");
									title();
									puts("Please input lower or equal than the total stock(s) available.");
								}
								printf("Total stock(s) for %s: %lld\n", data1[index].barang, data1[index].quantity);
								printf("Price of %s: %lld\n", data1[index].barang, data1[index].price);
								printf("Input: ");
								scanf("%lld", &purchase); getchar();
							}
							
							// harga total wajib ditambahkan setiap pembelian yang berhasil
							total += data1[index].price * purchase;
							
							// kuantitas/stok produk dikurangi dengan jumlah stok yang dibeli
							data1[index].quantity -= purchase;
							
							// program untuk menyimpan data yang dibeli customer
							strcpy(purchased[countIndex].barang, data1[index].barang); // countIndex akan dimulai dari 0
							strcpy(purchased[countIndex].code, data1[index].code);
							purchased[countIndex].quantity = purchase;
							purchased[countIndex].price = data1[index].price * purchase;
							
							// countIndex bertambah, untuk index pembelian berikutnya
							countIndex++;
							
							// totalPurchased berguna untuk display produk yang dibeli customer
							totalPurchased++;
							
							// display produk yang dibeli customer
							system("cls");
							title();
							puts("You have just purchased:\n");
							displayPurchased(purchased, totalPurchased);
							system("pause");
							puts("\nSuccessfully saved the purchase!\n");
							system("pause");
							system("cls");
							
							// display untuk sisa produk yang tersedia
							title();
							displayAvailable(size);
							system("pause");
							system("cls");
						}
						
						// bila produk yang diinginkan sudah habis stoknya
						else if(data1[index].quantity == 0) {
							puts("Sorry, product is out of stock.\n");
							system("pause"); // dibalikkan ke input menu.
						}
					}
					break;
				}
				
				// Finish Sales
				case 2: {
					int persen;
					ll diskon = 0;
					ll result = 0;
					if(total >= 1000000) {
						persen = 10;
						diskon += 0.1 * total;
					}
					else if(total > 500000) {
						persen = 8;
						diskon += 0.08 * total;
					}
					else if(total > 300000) {
						persen = 5;
						diskon += 0.05 * total;
					}
					
					result += total - diskon;
					
					// display barang yang telah dibeli customer
					printf("Thank you %s for shopping!\n\n", name);
					puts("Purchase List:");
					displayPurchased(purchased, totalPurchased);
					printf("Total Price: %lld\n", total);
					printf("Total Discount: %lld percent\n", persen);
					printf("Discount Amount: %lld\n", diskon);
					printf("Amount Due: %lld\n\n", result);
					
					// program sudah selesai, maka akan diminta untuk menginput nama customer yang baru
					newSales = 0; // agar balik lagi ke input nama customer
					done = 1; // agar program berakhir
					system("pause");
					
					// membuat file/struk [customer].txt
					char temp1[100];
					strcpy(temp1, name);
					strcat(temp1, ".txt");
					customerFile(purchased, temp1, name, totalPurchased, total, persen, diskon, result);
					break;
				}
				
				// Exit
				case 3: {
					// hanya diminta update stok produk yang tersedia saja
					FILE *update;
					update = fopen("data.txt", "w");
					for(int i = 0 ; i < size; i++) {
						if(i == size - 1) fprintf(update, "%s#%s#%lld#%lld", data1[i].code, data1[i].barang, data1[i].quantity, data1[i].price);
						else fprintf(update, "%s#%s#%lld#%lld\n", data1[i].code, data1[i].barang, data1[i].quantity, data1[i].price);
					}
					fclose(update);
					printf("Thank you for using this program!\n");
					done = 1; // program sudah selesai, langsung return 0
					break;
				}
			}
		}
	}
	
	fclose(fp);
	return 0;
}

void title() {
	puts("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+");
	puts("=                    SALES PROGRAM                    =");
	puts("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
}

void displayPurchased(struct data purchased[], ll totalPurchased) {
	puts("Code         Products          Quantity      Price");
	puts("====================================================");
	for(int i = 0; i < totalPurchased; i++) {
		printf("%-12s %-20s %-10lld %lld", purchased[i].code, purchased[i].barang, purchased[i].quantity, purchased[i].price);
		puts("");
	}
	puts("====================================================\n");
}

void displayAvailable(ll size) {
	puts("Here are all the stocks available:\n");
	puts("Code         Products          Quantity      Price");
	puts("==================================================");
	for(int i = 0; i < size; i++) {
		printf("%-12s %-20s %-10lld %lld", data1[i].code, data1[i].barang, data1[i].quantity, data1[i].price);
		puts("");
	}
	puts("==================================================\n");
}

void customerFile(struct data purchased[], char temp1[], char name[], ll totalPurchased, ll total, int persen, ll diskon, ll result) {
	FILE *customer;
	customer = fopen(temp1, "w");
	fprintf(customer, "Thank you %s for shopping!\n\n", name);
	fprintf(customer, "Purchase List:\n");
	fprintf(customer, "Code         Products          Quantity      Price\n");
	fprintf(customer, "====================================================\n");
	for(int i = 0; i < totalPurchased; i++) {
		fprintf(customer, "%-12s %-20s %-10lld %lld\n", purchased[i].code, purchased[i].barang, purchased[i].quantity, purchased[i].price);
		fprintf(customer, "");
	}
	fprintf(customer, "====================================================\n\n");
	fprintf(customer, "Total Price: %lld\n", total);
	fprintf(customer, "Total Discount: %lld percent\n", persen);
	fprintf(customer, "Discount Amount: %lld\n", diskon);
	fprintf(customer, "Amount Due: %lld", result);
	fclose(customer);
}