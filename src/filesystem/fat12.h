#pragma once

#include <map>
#include <array>
#include <vector>
#include <string_view>

using uchar = unsigned char;

auto get_word(const std::vector<uchar>& v, size_t pos) -> uint32_t;
auto get_hword(const std::vector<uchar>& v, size_t pos) -> uint16_t;

enum media_type {
    floppy,
    DOS,
    ram_disk,
    hard_disk,
    unknown,
};

struct media_descriptor {
    std::string name{""};
    uint16_t capacity{0};
    uint8_t sides{ 0 };
    uint8_t tracks{ 0 };
    uint8_t sectors_per_track{ 0 };
    media_type type{ unknown };
};

struct directory;

/* Here FAT stands for File Allocation Table : the disk is divided into clusters,
 * the unit used by the file allocation, and the FAT describes which clusters
 * are used by which files.
 */
struct fat12 {
    fat12(std::string_view path);
    auto ls() -> std::vector<std::string>;
    auto root() -> size_t {
        size_t fat_location = reserved_sectors * bytes_per_sector;
        size_t root_location = sectors_per_fat * bytes_per_sector * fat_copies +
            fat_location;
        return root_location;
    }

    std::vector<uchar> fs;

    uint32_t jmp_to_bootstrap;
    std::string OEM_name;
    uint16_t bytes_per_sector; // 512, 1k, 2k, 4k
    // TODO: check sectors per cluster are correct respect to cluster size
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

    media_descriptor fs_description;
};