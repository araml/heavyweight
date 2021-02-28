#pragma once

#include <fat12.h>
#include <string>
#include <vector>

// (TODO): name chars must be filtered for erroneous names
struct directory_entry {
    directory_entry(const std::vector<uchar>& fat, size_t idx) {
        for (size_t i = 0; i < 11; i++)
            file_name.push_back(fat[i + idx]);

        attr = fat[idx + 11];

        for (size_t i = 0; i < 10; i++)
            reserved[i] = fat[i + idx + 12];

        time = get_hword(fat, idx + 22);
        date = get_hword(fat, idx + 24);
        starting_cluster = get_hword(fat, idx + 26);
        filesize = get_word(fat, idx + 28);
    }

    std::string file_name;
    uint8_t attr;
    std::array<uchar, 10> reserved;
    uint16_t time;
    uint16_t date;
    uint16_t starting_cluster;
    uint32_t filesize;
};

struct directory {
    directory(fat12& f, size_t idx) : fat(f), idx(idx) {}

    struct iterator {
        iterator(const std::vector<uchar>& arr, size_t idx) :
            fat(arr), idx(idx) {
        }

        auto operator==(iterator& rhs) -> bool {
            return idx == rhs.idx;
        }

        auto operator!=(iterator& rhs) -> bool {
            return !(*this == rhs);
        }

        auto operator++() -> void {
            idx += 32;
        }

        const std::vector<uchar>& fat;
        size_t idx;
        size_t n_entries;

        auto operator*() -> directory_entry {
            return directory_entry(fat, idx);
        }
        auto operator->() -> directory_entry {
            return directory_entry(fat, idx);
        }
    };

    auto begin() -> iterator {
        return iterator(fat.fs, idx);
    }
    auto end() -> iterator {
        return iterator(fat.fs, idx + fat.root_dir_entries * 32);
    }

    fat12& fat;
    size_t idx;
};

