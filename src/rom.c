#include <rom.h>
#include <string.h>

Mapper* load_rom(const char* filename, size_t* length) {
    Mapper* mapper = (Mapper*)malloc(sizeof(Mapper));
    printf("file name - %s\n", filename);
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *file_bytes = (uint8_t*)malloc(file_size + 1);
    if (!file_bytes) {
        printf("Failed to allocate memory");
        fclose(file);
        return NULL;
    }
    size_t bytes_read = fread(file_bytes, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("Failed to read the full file");
        free(file_bytes);
        fclose(file);
        return NULL;
    }

    file_bytes[file_size] = '\0';
    uint8_t mapper_number = (file_bytes[6] & 0xF0) >> 4 | file_bytes[7] & 0xF0;
    printf("mapper number: %d\n", mapper_number);

    int prg_size = file_bytes[4];
    int chr_size = file_bytes[5];
    printf("prg size: %d, chr size: %d\n", prg_size, chr_size);
    int prg_unit_size = 16384;
    int chr_unit_size = 8192;
    switch (mapper_number) {
        case 0: {
            mapper->prg_start = 0x6000;
            mapper->prg_end = 0xFFFF;
            mapper->prg_len = prg_unit_size * 3;
            mapper->prg = (uint8_t *)malloc(mapper->prg_len);
            memset(mapper->prg, 0x00, prg_unit_size);
            // memcpy(mapper.prg, &file_bytes[16], prg_unit_size);
            memcpy(mapper->prg + prg_unit_size, &file_bytes[16], prg_unit_size);
            if (prg_size == 1) {
                memcpy(mapper->prg + prg_unit_size * 2, &file_bytes[16], prg_unit_size);
            } else {
                memcpy(mapper->prg + prg_unit_size * 2, &file_bytes[16 + prg_unit_size], prg_unit_size);
            }
            mapper->chr_len = chr_unit_size * chr_size;
            mapper->chr = (uint8_t *)malloc(mapper->chr_len);
            memcpy(mapper->chr, &file_bytes[16 + prg_unit_size * prg_size], mapper->chr_len);
            break;
        }
        default:
            break;
    }
    // for(size_t i = 0; i < mapper->chr_len; i++) {
    //     printf("%u ", mapper->chr[i]);
    // }

    // printf("\n");
    return mapper;
}

// void write_prg(Mapper *mapper, uint16_t address, uint8_t data) {
// }

uint8_t read_prg(Mapper *mapper, uint16_t address) {
    if (address >= 0x6000 && 0xFFFF >= address)
        return * (mapper->prg + (address - 0x6000));
    return 0x00;
}

void free_rom(Mapper *mapper) {
    free(mapper->prg);
    free(mapper->chr);
    free(mapper);
}

