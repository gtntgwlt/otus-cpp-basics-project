#include <iostream>
#include <fmt/color.h>
#include <string>
#include "lexer.h"
#include "printer_common.h"

#include <fmt/color.h>

/*
    мб предобработка файла тут. узнать язык, посчитать количество строк
    в лекс передать инфо об языке для загрузки конфига
*/

void show_color()
{
    fmt::print(fg(fmt::color::alice_blue), "\nalice_blue ");
    fmt::print(fg(fmt::color::antique_white), "antique_white ");
    fmt::print(fg(fmt::color::aqua), "aqua ");
    fmt::print(fg(fmt::color::aquamarine), "aquamarine ");
    fmt::print(fg(fmt::color::azure), "azure ");
    fmt::print(fg(fmt::color::beige), "beige ");
    fmt::print(fg(fmt::color::bisque), "bisque ");
    fmt::print(fg(fmt::color::black), "black ");
    fmt::print(fg(fmt::color::blanched_almond), "blanched_almond ");
    fmt::print(fg(fmt::color::blue), "blue ");
    fmt::print(fg(fmt::color::blue_violet), "blue_violet \n");

    fmt::print(fg(fmt::color::brown), "brown ");
    fmt::print(fg(fmt::color::burly_wood), "burly_wood ");
    fmt::print(fg(fmt::color::cadet_blue), "cadet_blue ");
    fmt::print(fg(fmt::color::chartreuse), "chartreuse ");
    fmt::print(fg(fmt::color::chocolate), "chocolate ");
    fmt::print(fg(fmt::color::coral), "coral ");
    fmt::print(fg(fmt::color::cornflower_blue), "cornflower_blue ");
    fmt::print(fg(fmt::color::cornsilk), "cornsilk ");
    fmt::print(fg(fmt::color::crimson), "crimson ");
    fmt::print(fg(fmt::color::cyan), "cyan \n");

    fmt::print(fg(fmt::color::dark_blue), "dark_blue ");
    fmt::print(fg(fmt::color::dark_cyan), "dark_cyan ");
    fmt::print(fg(fmt::color::dark_golden_rod), "dark_golden_rod ");
    fmt::print(fg(fmt::color::dark_gray), "dark_gray ");
    fmt::print(fg(fmt::color::dark_green), "dark_green ");
    fmt::print(fg(fmt::color::dark_khaki), "dark_khaki ");
    fmt::print(fg(fmt::color::dark_magenta), "dark_magenta ");
    fmt::print(fg(fmt::color::dark_olive_green), "dark_olive_green ");
    fmt::print(fg(fmt::color::dark_orange), "dark_orange ");
    fmt::print(fg(fmt::color::dark_orchid), "dark_orchid \n");

    fmt::print(fg(fmt::color::dark_red), "dark_red ");
    fmt::print(fg(fmt::color::dark_salmon), "dark_salmon ");
    fmt::print(fg(fmt::color::dark_sea_green), "dark_sea_green ");
    fmt::print(fg(fmt::color::dark_slate_blue), "dark_slate_blue ");
    fmt::print(fg(fmt::color::dark_slate_gray), "dark_slate_gray ");
    fmt::print(fg(fmt::color::dark_turquoise), "dark_turquoise ");
    fmt::print(fg(fmt::color::dark_violet), "dark_violet ");
    fmt::print(fg(fmt::color::deep_pink), "deep_pink ");
    fmt::print(fg(fmt::color::deep_sky_blue), "deep_sky_blue ");
    fmt::print(fg(fmt::color::dim_gray), "dim_gray \n");

    fmt::print(fg(fmt::color::dodger_blue), "dodger_blue ");
    fmt::print(fg(fmt::color::fire_brick), "fire_brick ");
    fmt::print(fg(fmt::color::floral_white), "floral_white ");
    fmt::print(fg(fmt::color::forest_green), "forest_green ");
    fmt::print(fg(fmt::color::fuchsia), "fuchsia ");
    fmt::print(fg(fmt::color::gainsboro), "gainsboro ");
    fmt::print(fg(fmt::color::ghost_white), "ghost_white ");
    fmt::print(fg(fmt::color::gold), "gold ");
    fmt::print(fg(fmt::color::golden_rod), "golden_rod ");
    fmt::print(fg(fmt::color::gray), "gray \n");

    fmt::print(fg(fmt::color::green), "green ");
    fmt::print(fg(fmt::color::green_yellow), "green_yellow ");
    fmt::print(fg(fmt::color::honey_dew), "honey_dew ");
    fmt::print(fg(fmt::color::hot_pink), "hot_pink ");
    fmt::print(fg(fmt::color::indian_red), "indian_red ");
    fmt::print(fg(fmt::color::indigo), "indigo ");
    fmt::print(fg(fmt::color::ivory), "ivory ");
    fmt::print(fg(fmt::color::khaki), "khaki ");
    fmt::print(fg(fmt::color::lavender), "lavender ");
    fmt::print(fg(fmt::color::lavender_blush), "lavender_blush \n");

    fmt::print(fg(fmt::color::lawn_green), "lawn_green ");
    fmt::print(fg(fmt::color::lemon_chiffon), "lemon_chiffon ");
    fmt::print(fg(fmt::color::light_blue), "light_blue ");
    fmt::print(fg(fmt::color::light_coral), "light_coral ");
    fmt::print(fg(fmt::color::light_cyan), "light_cyan ");
    fmt::print(fg(fmt::color::light_golden_rod_yellow), "light_golden_rod_yellow ");
    fmt::print(fg(fmt::color::light_gray), "light_gray ");
    fmt::print(fg(fmt::color::light_green), "light_green ");
    fmt::print(fg(fmt::color::light_pink), "light_pink ");
    fmt::print(fg(fmt::color::light_salmon), "light_salmon \n");

    fmt::print(fg(fmt::color::light_sea_green), "light_sea_green ");
    fmt::print(fg(fmt::color::light_sky_blue), "light_sky_blue ");
    fmt::print(fg(fmt::color::light_slate_gray), "light_slate_gray ");
    fmt::print(fg(fmt::color::light_steel_blue), "light_steel_blue ");
    fmt::print(fg(fmt::color::light_yellow), "light_yellow ");
    fmt::print(fg(fmt::color::lime), "lime ");
    fmt::print(fg(fmt::color::lime_green), "lime_green ");
    fmt::print(fg(fmt::color::linen), "linen ");
    fmt::print(fg(fmt::color::magenta), "magenta ");
    fmt::print(fg(fmt::color::maroon), "maroon \n");

    fmt::print(fg(fmt::color::medium_aquamarine), "medium_aquamarine ");
    fmt::print(fg(fmt::color::medium_blue), "medium_blue ");
    fmt::print(fg(fmt::color::medium_orchid), "medium_orchid ");
    fmt::print(fg(fmt::color::medium_purple), "medium_purple ");
    fmt::print(fg(fmt::color::medium_sea_green), "medium_sea_green ");
    fmt::print(fg(fmt::color::medium_slate_blue), "medium_slate_blue ");
    fmt::print(fg(fmt::color::medium_spring_green), "medium_spring_green ");
    fmt::print(fg(fmt::color::medium_turquoise), "medium_turquoise ");
    fmt::print(fg(fmt::color::medium_violet_red), "medium_violet_red ");
    fmt::print(fg(fmt::color::midnight_blue), "midnight_blue \n");

    fmt::print(fg(fmt::color::mint_cream), "mint_cream ");
    fmt::print(fg(fmt::color::misty_rose), "midnight_blue ");
    fmt::print(fg(fmt::color::moccasin), "moccasin ");
    fmt::print(fg(fmt::color::navajo_white), "navajo_white ");
    fmt::print(fg(fmt::color::navy), "navy ");
    fmt::print(fg(fmt::color::old_lace), "old_lace ");
    fmt::print(fg(fmt::color::olive), "olive ");
    fmt::print(fg(fmt::color::olive_drab), "olive_drab ");
    fmt::print(fg(fmt::color::orange), "orange ");
    fmt::print(fg(fmt::color::orange_red), "orange_red \n");

    fmt::print(fg(fmt::color::orchid), "orchid ");
    fmt::print(fg(fmt::color::pale_golden_rod), "pale_golden_rod ");
    fmt::print(fg(fmt::color::pale_green), "pale_green ");
    fmt::print(fg(fmt::color::pale_turquoise), "pale_turquoise ");
    fmt::print(fg(fmt::color::pale_violet_red), "pale_violet_red ");
    fmt::print(fg(fmt::color::papaya_whip), "papaya_whip ");
    fmt::print(fg(fmt::color::peach_puff), "peach_puff ");
    fmt::print(fg(fmt::color::peru), "peru ");
    fmt::print(fg(fmt::color::pink), "pink ");
    fmt::print(fg(fmt::color::plum), "plum \n");

    fmt::print(fg(fmt::color::powder_blue), "powder_blue ");
    fmt::print(fg(fmt::color::purple), "purple ");
    fmt::print(fg(fmt::color::rebecca_purple), "rebecca_purple ");
    fmt::print(fg(fmt::color::red), "red ");
    fmt::print(fg(fmt::color::rosy_brown), "rosy_brown ");
    fmt::print(fg(fmt::color::royal_blue), "royal_blue ");
    fmt::print(fg(fmt::color::saddle_brown), "saddle_brown ");
    fmt::print(fg(fmt::color::salmon), "salmon ");
    fmt::print(fg(fmt::color::sandy_brown), "sandy_brown ");
    fmt::print(fg(fmt::color::sea_green), "sea_green \n");

    fmt::print(fg(fmt::color::sea_shell), "sea_shell ");
    fmt::print(fg(fmt::color::sienna), "sienna ");
    fmt::print(fg(fmt::color::silver), "silver ");
    fmt::print(fg(fmt::color::sky_blue), "sky_blue ");
    fmt::print(fg(fmt::color::slate_blue), "slate_blue ");
    fmt::print(fg(fmt::color::slate_gray), "slate_gray ");
    fmt::print(fg(fmt::color::snow), "snow ");
    fmt::print(fg(fmt::color::spring_green), "spring_green ");
    fmt::print(fg(fmt::color::steel_blue), "steel_blue ");
    fmt::print(fg(fmt::color::tan), "tan \n");

    fmt::print(fg(fmt::color::teal), "teal ");
    fmt::print(fg(fmt::color::thistle), "thistle ");
    fmt::print(fg(fmt::color::tomato), "tomato ");
    fmt::print(fg(fmt::color::turquoise), "turquoise ");
    fmt::print(fg(fmt::color::violet), "violet ");
    fmt::print(fg(fmt::color::wheat), "wheat ");
    fmt::print(fg(fmt::color::white), "white ");
    fmt::print(fg(fmt::color::white_smoke), "white_smoke ");
    fmt::print(fg(fmt::color::yellow), "yellow ");
    fmt::print(fg(fmt::color::yellow_green), "yellow_green ");
}

int main(int argc, const char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Filename needed" << std::endl;
        exit(1);
    }
    //show_color();
    std::string filename = argv[1];
    Lexer lex(filename);
    Printer *out; // do smart pointer
    if (lex.get_language() == "c")
        out = new C_Printer(lex);
    else
        out = new Printer(lex);

    out->print();

    delete out;
    std::cout << std::endl << std::endl;
    return 0;
}

