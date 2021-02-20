#ifndef CLASSIC_EVAL_PST_HPP
#define CLASSIC_EVAL_PST_HPP

#include <libchess/piece.hpp>
#include <libchess/side.hpp>
#include <libchess/square.hpp>
#include "../score.hpp"

// clang-format off
constexpr Score pst[6][64] = 
{
    {
        {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     
        {-1,-17},  {-7,-17},  {-11,-17}, {-35,-17}, {-13,-17}, {5,-17},   {3,-17},   {-5,-17},  
        {1,-11},   {1,-11},   {-6,-11},  {-19,-11}, {-6,-11},  {-7,-11},  {-4,-11},  {10,-11},  
        {1,-7},    {14,-7},   {8,-7},    {4,-7},    {5,-7},    {4,-7},    {10,-7},   {7,-7},    
        {9,16},    {30,16},   {23,16},   {31,16},   {31,16},   {23,16},   {17,16},   {11,16},   
        {21,55},   {54,55},   {72,55},   {56,55},   {77,55},   {95,55},   {71,55},   {11,55},   
        {118,82},  {121,82},  {173,82},  {168,82},  {107,82},  {82,82},   {-16,82},  {22,82},   
        {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     {0,0},     
    },{
        {-99,-99}, {-30,-99}, {-66,-94}, {-64,-88}, {-29,-88}, {-19,-94}, {-61,-99}, {-81,-99}, 
        {-56,-81}, {-31,-62}, {-28,-49}, {-1,-43},  {-7,-43},  {-20,-49}, {-42,-62}, {-11,-81}, 
        {-38,-46}, {-16,-27}, {0,-15},   {14,-9},   {8,-9},    {3,-15},   {3,-27},   {-42,-46}, 
        {-14,-22}, {0,-3},    {2,10},    {3,16},    {19,16},   {12,10},   {33,-3},   {-7,-22},  
        {-14,-7},  {-4,12},   {25,25},   {33,31},   {10,31},   {33,25},   {14,12},   {43,-7},   
        {-22,-2},  {18,17},   {60,30},   {64,36},   {124,36},  {143,30},  {55,17},   {6,-2},    
        {-34,-7},  {24,12},   {54,25},   {74,31},   {60,31},   {122,25},  {2,12},    {29,-7},   
        {-60,-21}, {0,-3},    {0,10},    {0,16},    {0,16},    {0,10},    {0,-3},    {0,-21},   
    },{
        {-7,-27},  {12,-21},  {-8,-17},  {-37,-15}, {-31,-15}, {-8,-17},  {-45,-21}, {-67,-27}, 
        {15,-10},  {5,-4},    {13,0},    {-10,2},   {1,2},     {2,0},     {0,-4},    {15,-10},  
        {5,2},     {12,8},    {14,12},   {13,14},   {10,14},   {-1,12},   {3,8},     {4,2},     
        {1,11},    {5,17},    {23,21},   {32,23},   {21,23},   {8,21},    {17,17},   {4,11},    
        {-1,14},   {16,20},   {29,24},   {27,26},   {37,26},   {27,24},   {17,20},   {4,14},    
        {7,13},    {27,19},   {20,23},   {56,25},   {91,25},   {108,23},  {53,19},   {44,13},   
        {-24,8},   {-23,14},  {30,18},   {58,20},   {65,20},   {61,18},   {69,14},   {11,8},    
        {0,-2},    {0,4},     {0,8},     {0,10},    {0,10},    {0,8},     {0,4},     {0,-2},    
    },{
        {-2,-32},  {-1,-31},  {3,-30},   {1,-29},   {2,-29},   {1,-30},   {4,-31},   {-8,-32},  
        {-26,-27}, {-6,-25},  {2,-24},   {-2,-24},  {2,-24},   {-10,-24}, {-1,-25},  {-29,-27}, 
        {-16,-15}, {0,-13},   {3,-12},   {-3,-12},  {8,-12},   {-1,-12},  {12,-13},  {3,-15},   
        {-9,1},    {-5,2},    {8,3},     {14,4},    {18,4},    {-17,3},   {13,2},    {-13,1},   
        {19,15},   {33,17},   {46,18},   {57,18},   {53,18},   {39,18},   {53,17},   {16,15},   
        {24,25},   {83,27},   {54,28},   {75,28},   {134,28},  {144,28},  {85,27},   {75,25},   
        {46,27},   {33,28},   {64,29},   {62,30},   {91,30},   {89,29},   {70,28},   {104,27},  
        {84,16},   {0,17},    {0,18},    {37,19},   {124,19},  {0,18},    {0,17},    {153,16},  
    },{
        {1,-61},   {-10,-55}, {-11,-52}, {3,-50},   {-15,-50}, {-51,-52}, {-83,-55}, {-13,-61}, 
        {-7,-31},  {3,-26},   {2,-22},   {5,-21},   {-1,-21},  {-10,-22}, {-7,-26},  {-2,-31},  
        {-11,-8},  {0,-3},    {12,1},    {2,3},     {8,3},     {11,1},    {7,-3},    {-6,-8},   
        {-9,9},    {5,14},    {7,17},    {9,19},    {18,19},   {17,17},   {26,14},   {4,9},     
        {-6,19},   {0,24},    {15,28},   {25,30},   {32,30},   {9,28},    {26,24},   {12,19},   
        {-16,23},  {10,28},   {13,32},   {25,34},   {37,34},   {30,32},   {15,28},   {26,23},   
        {1,21},    {11,26},   {35,30},   {0,31},    {16,31},   {55,30},   {39,26},   {57,21},   
        {-13,12},  {6,17},    {-42,21},  {0,23},    {29,23},   {0,21},    {0,17},    {102,12},  
    },{
        {0,-34},   {0,-30},   {0,-28},   {-9,-27},  {0,-27},   {-9,-28},  {25,-30},  {0,-34},   
        {-9,-17},  {-9,-13},  {-9,-11},  {-9,-10},  {-9,-10},  {-9,-11},  {-9,-13},  {-9,-17},  
        {-9,-2},   {-9,2},    {-9,4},    {-9,5},    {-9,5},    {-9,4},    {-9,2},    {-9,-2},   
        {-9,11},   {-9,15},   {-9,17},   {-9,18},   {-9,18},   {-9,17},   {-9,15},   {-9,11},   
        {-9,22},   {-9,26},   {-9,28},   {-9,29},   {-9,29},   {-9,28},   {-9,26},   {-9,22},   
        {-9,31},   {-9,34},   {-9,37},   {-9,38},   {-9,38},   {-9,37},   {-9,34},   {-9,31},   
        {-9,38},   {-9,41},   {-9,44},   {-9,45},   {-9,45},   {-9,44},   {-9,41},   {-9,38},   
        {-9,42},   {-9,46},   {-9,48},   {-9,50},   {-9,50},   {-9,48},   {-9,46},   {-9,42},   
    },
};
// clang-format on

template <libchess::Side side>
[[nodiscard]] constexpr Score pst_value(const libchess::Piece piece, const libchess::Square sq) {
    if constexpr (side == libchess::Side::White) {
        return pst[piece][static_cast<int>(sq)];
    } else {
        return pst[piece][static_cast<int>(sq.flip())];
    }
}

#endif
