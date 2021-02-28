#include <fat12.h>
#include <stdio.h>
#include <iostream>

static auto load_image(std::string_view path) -> std::vector<uchar> {
    FILE* fp = fopen(path.data(), "rb");
    fseek(fp, 0, SEEK_END);
    size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    std::vector<uchar> tmp(length);
    fread(tmp.data(), sizeof(uchar), tmp.size(), fp);
    return tmp;
}

// its actually 3 bytes :^)
auto get_word(const std::vector<uchar> &v, size_t pos) -> uint32_t {
    uint32_t result{ 0 };
    result = v[pos + 2] << 16;
    result |= v[pos + 1] << 8;
    result |= v[pos + 0];
    return result;
}

auto get_hword(const std::vector<uchar> &v, size_t pos) -> uint16_t {
    uint16_t result{0};
    result = v[pos + 1] << 8;
    result |= v[pos];
    return result;
}

fat12::fat12(std::string_view path) {
    fs = load_image(path);
    jmp_to_bootstrap = get_word(fs, 0);
    for (size_t i = 3; i <= 10; i++)
        OEM_name.push_back(fs[i]);
    bytes_per_sector = get_hword(fs, 11);
    sectors_per_cluster = fs[13];
    reserved_sectors = get_hword(fs, 14);
    fat_copies = fs[16];
    root_dir_entries = get_hword(fs, 17);
    total_sectors_in_fs = get_hword(fs, 19);
    media_descriptor_type = fs[21];
    sectors_per_fat = get_hword(fs, 22);
    sectors_per_track = get_hword(fs, 24);
    number_of_heads = get_hword(fs, 26);
    number_of_hidden_sectors = get_hword(fs, 28);
    for (size_t i = 30; i < 509; i++)
        bootstrap[i - 30] = fs[i];
    signature = get_hword(fs, 510);
}

auto fat12::ls() -> std::vector<std::string> {
    size_t fat_location = reserved_sectors * bytes_per_sector;
    size_t root_location = sectors_per_fat * bytes_per_sector * fat_copies +
                           fat_location;
    size_t fat_size = sectors_per_fat * bytes_per_sector;
    /*
    std::vector<directory_entry> dir_entries;
    for (size_t idx = 0; idx < root_dir_entries; idx++) {
        directory_entry dir(fs, idx * 32 + root_location);
        if (dir.starting_cluster)
            dir_entries.push_back(dir);
    }*/

    return {};
}
