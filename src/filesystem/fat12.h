#pragma once

#include <array>
#include <vector>
#include <string_view>

using uchar = unsigned char;

struct fat12 {
    fat12(std::string_view path);
    std::vector<uchar> fs;

    uint32_t jmp_to_bootstrap;
    std::string OEM_name;
    uint16_t bytes_per_sector; // 512, 1k, 2k, 4k
    uint8_t sectors_per_cluster; // only multiples of 2.
    uint16_t reserved_sectors;
    uint8_t fat_copies;
    uint16_t root_dir_entries;
    uint16_t total_sectors_in_fs;
    uint8_t media_descriptor_type;    
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint16_t number_of_hidden_sectors;
    std::array<uchar, 479> bootstrap;
    uint16_t signature;
};