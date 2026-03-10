//12S25003-Afrian Josse Siadari

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void format_currency(long long amount, char *output_buffer, int buffer_size) {
    char temp_num_str[50];
    sprintf(temp_num_str, "%lld", amount);

    int len = strlen(temp_num_str);
    int dot_count = (len - 1) / 3;
    
    int num_part_len = len + dot_count; 
    
    int total_req_len = 3 + num_part_len + 1;

    if (total_req_len > buffer_size) {
        snprintf(output_buffer, buffer_size, "Rp.%lld (BufOvF)", amount); 
        return;
    }

    output_buffer[total_req_len - 1] = '\0';

    int output_idx = total_req_len - 2; 
    int temp_idx = len - 1; 
    int digits_processed = 0;

    while (temp_idx >= 0) {
        output_buffer[output_idx--] = temp_num_str[temp_idx--];
        digits_processed++;
        if (digits_processed % 3 == 0 && temp_idx >= 0) {
            output_buffer[output_idx--] = '.';
        }
    }
    
    output_buffer[0] = 'R';
    output_buffer[1] = 'p';
    output_buffer[2] = '.';
}


int main() {
    const char *NOMOR_REKENING_KOPERASI = "123456789";
    const long long HARGA_DASAR_TUJUAN_PER_ORANG = 20000; 

    const long long HARGA_BUS_REGULER_PER_ORANG = 40000; 
    const long long HARGA_MOBIL_PRIBADI_PER_ORANG = 80000; 
    const long long HARGA_MINIBUS_PER_ORANG = 35000; 

    const char *waktu_keberangkatan_options[] = {
        "08:00 (Pagi)", "10:00 (Pagi)", "13:00 (Siang)", "15:00 (Sore)",
        "21:00 (Malam)", "00:00 (Tengah Malam)", "02:00 (Subuh)"
    };
    int num_waktu_keberangkatan_options = sizeof(waktu_keberangkatan_options) / sizeof(waktu_keberangkatan_options[0]);

    const char *tujuan_options[] = {"Medan", "Parapat", "Dolok Sanggul"};
    int num_tujuan_options = sizeof(tujuan_options) / sizeof(tujuan_options[0]);

    const char *asal_perjalanan_options[] = {"Laguboti", "Parapat", "Dolok Sanggul"};
    int num_asal_perjalanan_options = sizeof(asal_perjalanan_options) / sizeof(asal_perjalanan_options[0]);
    
    const char *jenis_kendaraan_options[] = {"Bus Reguler", "Mobil Pribadi", "Minibus"};
    int num_jenis_kendaraan_options = sizeof(jenis_kendaraan_options) / sizeof(jenis_kendaraan_options[0]);


    char nama_pelanggan[100];
    char nomor_telepon_pelanggan[20];
    int jumlah_penumpang;
    char tanggal_order[20];
    char asal_perjalanan_pilihan[100];
    char waktu_keberangkatan_pilihan[50];
    char jenis_kendaraan_pilihan[50];
    char tujuan_pilihan[100];
    long long harga_per_orang;
    long long total_harga_final;
    long long harga_kendaraan_pilihan_per_orang = 0;
    char metode_pembayaran[50];
    char input_status_pembayaran_raw[20];
    char status_pembayaran_final[50];
    char status_pemesanan[50];

    char formatted_harga_dasar_per_orang[100];
    char formatted_harga_kendaraan_per_orang_output[100]; 
    char formatted_harga_per_orang_total[100];
    char formatted_total_harga_final_output[100];

    printf("---------------------------------------------------\n");
    printf("  Sistem Ticketing Koperasi Bintang Tapanuli\n");
    printf("---------------------------------------------------\n");
    printf("Silakan masukkan detail pemesanan Anda:\n\n");

    printf("Nama Pelanggan         : ");
    read_string(nama_pelanggan, sizeof(nama_pelanggan));

    printf("Nomor Telepon Pelanggan: ");
    read_string(nomor_telepon_pelanggan, sizeof(nomor_telepon_pelanggan));

    printf("Jumlah Penumpang       : ");
    scanf("%d", &jumlah_penumpang);
    while (getchar() != '\n');

    printf("Tanggal Order (contoh: DD-MM-YYYY): ");
    read_string(tanggal_order, sizeof(tanggal_order));

    printf("\nPilihan Asal Perjalanan:\n");
    for (int i = 0; i < num_asal_perjalanan_options; i++) {
        printf("  - %s\n", asal_perjalanan_options[i]);
    }
    printf("Asal Perjalanan        : ");
    read_string(asal_perjalanan_pilihan, sizeof(asal_perjalanan_pilihan));

    printf("\nPilihan Tujuan:\n");
    for (int i = 0; i < num_tujuan_options; i++) {
        printf("  - %s\n", tujuan_options[i]);
    }
    printf("Tujuan                 : ");
    read_string(tujuan_pilihan, sizeof(tujuan_pilihan));

    printf("\nPilihan Waktu Keberangkatan (KBT):\n");
    for (int i = 0; i < num_waktu_keberangkatan_options; i++) {
        printf("  - %s\n", waktu_keberangkatan_options[i]);
    }
    printf("Waktu Keberangkatan    : ");
    read_string(waktu_keberangkatan_pilihan, sizeof(waktu_keberangkatan_pilihan));

    printf("\nPilihan Jenis Kendaraan:\n");
    for (int i = 0; i < num_jenis_kendaraan_options; i++) {
        printf("  - %s\n", jenis_kendaraan_options[i]);
    }
    printf("Jenis Kendaraan        : ");
    read_string(jenis_kendaraan_pilihan, sizeof(jenis_kendaraan_pilihan));

    if (strcmp(jenis_kendaraan_pilihan, "Bus Reguler") == 0) {
        harga_kendaraan_pilihan_per_orang = HARGA_BUS_REGULER_PER_ORANG;
    } else if (strcmp(jenis_kendaraan_pilihan, "Mobil Pribadi") == 0) {
        harga_kendaraan_pilihan_per_orang = HARGA_MOBIL_PRIBADI_PER_ORANG;
    } else if (strcmp(jenis_kendaraan_pilihan, "Minibus") == 0) {
        harga_kendaraan_pilihan_per_orang = HARGA_MINIBUS_PER_ORANG;
    } else {
        printf("Jenis kendaraan tidak dikenali, harga default 0.\n");
        harga_kendaraan_pilihan_per_orang = 0;
    }

    harga_per_orang = HARGA_DASAR_TUJUAN_PER_ORANG + harga_kendaraan_pilihan_per_orang;

    total_harga_final = harga_per_orang * jumlah_penumpang;

    printf("Metode Pembayaran (Transfer Bank, Kartu Kredit, E-wallet): ");
    read_string(metode_pembayaran, sizeof(metode_pembayaran));

    printf("Input Status Pembayaran (ketik 'bayar', 'batalkan', atau '---'): ");
    read_string(input_status_pembayaran_raw, sizeof(input_status_pembayaran_raw));

    if (strcmp(input_status_pembayaran_raw, "bayar") == 0) {
        strcpy(status_pembayaran_final, "Dikonfirmasi");
    } else if (strcmp(input_status_pembayaran_raw, "batalkan") == 0) {
        strcpy(status_pembayaran_final, "Dibatalkan");
    } else if (strcmp(input_status_pembayaran_raw, "---") == 0) {
        strcpy(status_pembayaran_final, "Tertunda");
    } else {
        strcpy(status_pembayaran_final, "Status Tidak Valid");
    }

    strcpy(status_pemesanan, status_pembayaran_final);
    
    format_currency(HARGA_DASAR_TUJUAN_PER_ORANG, formatted_harga_dasar_per_orang, sizeof(formatted_harga_dasar_per_orang));
    format_currency(harga_kendaraan_pilihan_per_orang, formatted_harga_kendaraan_per_orang_output, sizeof(formatted_harga_kendaraan_per_orang_output));
    format_currency(harga_per_orang, formatted_harga_per_orang_total, sizeof(formatted_harga_per_orang_total));
    format_currency(total_harga_final, formatted_total_harga_final_output, sizeof(formatted_total_harga_final_output));

    printf("\n---------------------------------------------------\n");
    printf("          Ringkasan Pemesanan Anda\n");
    printf("---------------------------------------------------\n");
    printf("Nama Pelanggan         : %s\n", nama_pelanggan);
    printf("Nomor Telepon          : %s\n", nomor_telepon_pelanggan);
    printf("Jumlah Penumpang       : %d\n", jumlah_penumpang);
    printf("Tanggal Order          : %s\n", tanggal_order);
    printf("Asal Perjalanan        : %s\n", asal_perjalanan_pilihan);
    printf("Tujuan                 : %s\n", tujuan_pilihan);
    printf("Waktu Keberangkatan    : %s\n", waktu_keberangkatan_pilihan);
    printf("Jenis Kendaraan        : %s\n", jenis_kendaraan_pilihan);
    printf("Harga Dasar Tujuan/Org : %s\n", formatted_harga_dasar_per_orang);
    printf("Harga Kendaraan/Org    : %s\n", formatted_harga_kendaraan_per_orang_output);
    printf("Harga Per Orang Total  : %s\n", formatted_harga_per_orang_total);
    printf("TOTAL HARGA            : %s\n", formatted_total_harga_final_output); 
    printf("Metode Pembayaran      : %s\n", metode_pembayaran);
    printf("Status Pembayaran      : %s\n", status_pembayaran_final);
    printf("Status Pemesanan       : %s\n", status_pemesanan);
    printf("Nomor Rekening Koperasi: %s\n", NOMOR_REKENING_KOPERASI); 
    printf("---------------------------------------------------\n");

    return 0;
}
