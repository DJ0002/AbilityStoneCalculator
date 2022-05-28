
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "Calculator.h"
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "glad/glad.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void PerformReset(int hist[31], size_t smax, size_t s1, bool pickr1, bool p_m, bool sacrifice, long double &prob, long double &prob2, size_t r1p, size_t r2p, size_t r3p, size_t r12p, size_t r4p, size_t &r1s, size_t &r2s, size_t &r3s, size_t &row1, size_t &row2, size_t &row3, int &p, bool r1sh[10], bool r2sh[10], bool r3sh[10], int &choice, long double &r1e, long double &r2e, long double &r3e, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t) {
    r1s = 0; r2s = 0; r3s = 0; row1 = 0; row2 = 0; row3 = 0; p = 75;
    for (size_t i = 0; i < 10; i++) {
        r1sh[i] = false;
        r2sh[i] = false;
        r3sh[i] = false;
    }
    choice = dt[5][(smax * smax + smax + 1) * s1][0];
    r1e = exp[5][(smax * smax + smax + 1) * s1][0][0];
    for (size_t i = 0; i < 31; i++)
        hist[i] = 0;
    if (p_m) {
        r2e = expr2((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
        func11(r12p, r4p, prob2, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
        func12(r3p, r1p, r2p, prob, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
    }
    else r2e = exp[5][(smax * smax + smax + 1) * s1][0][1];
    if (sacrifice)
        r3e = expr3((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
    else r3e = base_e[5][23 * s1];
}

void FillTable1(size_t row, size_t column, bool base_d[6][200], long double base_e[6][231], int prob_i) {
    ImGui::Text("%f", base_e[prob_i][21 * (row + 1) + column]);
    if (base_d[prob_i][20 * row + column - 1]) {
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.28f, 0.68f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
}

void ColorCell1(size_t row, size_t column, size_t z, size_t smax, size_t r1st, size_t r2st, bool pickr1, std::vector<std::vector<std::vector<int>>>& dt, int prob_i) {
    if (pickr1) {
        if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 2) {}
        else if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 3) {
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.68f, 0.68f, 0.28f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.7f, 0.3f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
        else if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 0) {
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.28f, 0.68f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
        else {
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.68f, 0.28f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
    }
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 2) {}
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 3) {
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.68f, 0.68f, 0.28f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.7f, 0.3f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 0) {
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.68f, 0.28f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
    else {
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.28f, 0.68f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
}

void FillTable2(size_t row, size_t column, size_t z, size_t smax, size_t r1st, size_t r2st, size_t r3st, bool calc_done, bool p_m, bool sacrifice, bool pickr1, long double base_e[6][231], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i, std::vector<long double>& table_mem) {
    if (calc_done || table_mem[100 * z + 10 * row + column - 1] != -1) {
        ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
        ColorCell1(row, column, z, smax, r1st, r2st, pickr1, dt, prob_i);
    }
    else if (pickr1) {
        if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 2) {
            if (sacrifice)
                table_mem[100 * z + 10 * row + column - 1] = r3st + expr3(smax * smax * z + smax * column + row + 1, (smax - row - 1) * r1st + r2st, column, row + 1, z, r1st, r2st, r3st, prob_t, prob_i);
            else table_mem[100 * z + 10 * row + column - 1] = r3st + base_e[prob_i][21 * z + row + column + 1];
            ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
        }
        else if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 3) {
            table_mem[100 * z + 10 * row + column - 1] = r1st + exp[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st][0];
            ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.68f, 0.68f, 0.28f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.7f, 0.3f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
        else if (dt[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st] == 0) {
            table_mem[100 * z + 10 * row + column - 1] = r1st + exp[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st][0];
            ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.28f, 0.68f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
        else {
            if (p_m)
                table_mem[100 * z + 10 * row + column - 1] = r2st + expr2(smax * smax * z + smax * column + row + 1, (smax - row - 1) * r1st + r2st, column, row + 1, z, r1st, r2st, r3st, prob_t, prob_i);
            else table_mem[100 * z + 10 * row + column - 1] = r2st + exp[prob_i][smax * smax * z + smax * column + row + 1][(smax - row - 1) * r1st + r2st][1];
            ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
            if (row % 2 == 0) {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.68f, 0.28f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
            else {
                ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
            }
        }
    }
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 2) {
        if (sacrifice)
            table_mem[100 * z + 10 * row + column - 1] = r3st + expr3(smax * smax * z + smax * (row + 1) + column, (smax - column) * r1st + r2st, row + 1, column, z, r1st, r2st, r3st, prob_t, prob_i);
        else table_mem[100 * z + 10 * row + column - 1] = r3st + base_e[prob_i][21 * z + row + column + 1];
        ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
    }
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 3) {
        table_mem[100 * z + 10 * row + column - 1] = r1st + exp[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st][0];
        ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.68f, 0.68f, 0.28f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.7f, 0.3f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
    else if (dt[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st] == 0) {
        table_mem[100 * z + 10 * row + column - 1] = r1st + exp[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st][0];
        ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.68f, 0.28f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
    else {
        if (p_m)
            table_mem[100 * z + 10 * row + column - 1] = r2st + expr2(smax * smax * z + smax * (row + 1) + column, (smax - column) * r1st + r2st, row + 1, column, z, r1st, r2st, r3st, prob_t, prob_i);
        else table_mem[100 * z + 10 * row + column - 1] = r2st + exp[prob_i][smax * smax * z + smax * (row + 1) + column][(smax - column) * r1st + r2st][1];
        ImGui::Text("%f", table_mem[100 * z + 10 * row + column - 1]);
        if (row % 2 == 0) {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.28f, 0.28f, 0.68f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
        else {
            ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
        }
    }
}

void FillTable3(size_t row, size_t column, size_t z, size_t smax, size_t r1st, size_t r2st, size_t r3st, size_t r1pt, size_t r2pt, size_t r3pt, size_t r12pt, size_t r4pt, bool calc_done2, bool pickr1, std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, int prob_i, std::vector<long double>& table_mem2, std::vector<long double>& table_mem3) {
    if (calc_done2 || table_mem2[100 * z + 10 * row + column - 1] != -1)
        ImGui::Text("%.2f%%\n%.2f%%", table_mem2[100 * z + 10 * row + column - 1], table_mem3[100 * z + 10 * row + column - 1]);
    else {
        long double prob = 0, prob2 = 0;
        if (pickr1)
            update_probabilities(prob, prob2, 10 * prob_i + 25, smax, r1pt, r2pt, r3pt, r12pt, r4pt, smax - 1, r1st, r2st, r3st, smax - 1 - column, smax - row - 2, smax - 1 - z, prob_t);
        else update_probabilities(prob, prob2, 10 * prob_i + 25, smax, r1pt, r2pt, r3pt, r12pt, r4pt, smax - 1, r1st, r2st, r3st, smax - row - 2, smax - 1 - column, smax - 1 - z, prob_t);
        table_mem2[100 * z + 10 * row + column - 1] = 100 * prob;
        table_mem3[100 * z + 10 * row + column - 1] = 100 * prob2;
        ImGui::Text("%.2f%%\n%.2f%%", table_mem2[100 * z + 10 * row + column - 1], table_mem3[100 * z + 10 * row + column - 1]);
    }
    ColorCell1(row, column, z, smax, r1st, r2st, pickr1, dt, prob_i);
}

void ShowTables(bool* p_open, bool p_m, bool sacrifice, bool pickr1, bool &calc_done, bool &calc_done2, size_t s1, size_t smax, int &p, size_t &r1st, size_t &r2st, size_t &r3st, size_t& r1pt, size_t& r2pt, size_t& r3pt, size_t& r12pt, size_t& r4pt, long double base_e[6][231], bool base_d[6][200], std::vector<std::vector<std::vector<int>>>& dt, std::vector<std::vector<std::vector<std::vector<long double>>>>& exp, std::vector<std::vector<std::vector<std::vector<long double>>>>& prob_t, std::vector<long double>& table_mem, std::vector<long double>& table_mem2, std::vector<long double>& table_mem3) {
    ImGui::SetNextWindowSize(ImVec2(1089, 595), ImGuiCond_FirstUseEver);
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    if (!ImGui::Begin("Tables", p_open)) {
        ImGui::End();
        return;
    }
    if (ImGui::BeginTabBar("##TabBar")) {
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable;
        static ImGuiTableFlags flags2 = ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop;
        if (ImGui::BeginTabItem("Base Table")) {
            ImGui::Text("r1+r2 is the total remaining slots from row 1 and row 2");
            ImGui::Text("r3 is the total remaining slots from row 3");
            ImGui::ColorButton("##ColorButton", ImVec4(0.3f, 0.3f, 0.7f, 0.65f), flags2);
            ImGui::SameLine();
            ImGui::Text("means row 1 or row 2 is chosen and");
            ImGui::SameLine();
            ImGui::ColorButton("##ColorButton1", ImVec4(0.7f, 0.3f, 0.3f, 0.65f), flags2);
            ImGui::SameLine();
            ImGui::Text("means row 3 is chosen");
            if (ImGui::Button("Rate##1"))
                ImGui::OpenPopup("my_select_popup##1");
            ImGui::SameLine();
            ImGui::Text("%d%%", p);
            if (ImGui::BeginPopup("my_select_popup##1")) {
                for (int i = 0; i < 6; i++) {
                    char buf[32];
                    sprintf(buf, "%d%%", 25 + 10 * i);
                    if (ImGui::Selectable(buf))
                        p = 25 + 10 * i;
                }
                ImGui::EndPopup();
            }
            ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 16); //rows + 2 + new lines, and the +2 comes from row 1 labels and scroll bar
            ImGui::Text("Table 1: Expected value for successes in row 3 given r1+r2 vs r3");
            if (ImGui::BeginTable("r1 + r2 vs r3", 21, flags, outer_size)) {
                ImGui::TableSetupScrollFreeze(1, 1);
                ImGui::TableSetupColumn("\\r1   \n \\ +  \n  \\ r2\n   \\  \nr3  \\ \n     \\", ImGuiTableColumnFlags_NoHide);
                for (size_t i = 0; i < 20; i++) {
                    std::string s = "\n\n" + std::to_string(i + 1);
                    char* buf = &s[0];
                    ImGui::TableSetupColumn(buf);
                }
                ImGui::TableHeadersRow();
                for (size_t row = 0; row < 10; row++) {
                    ImGui::TableNextRow();
                    ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.3f, 0.3f, 0.65f));
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + 1, row_bg_color);
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%d", row + 1);
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.19f, 0.19f, 0.2f, 1.0f)));
                    for (size_t column = 1; column < 21; column++) {
                        if (!ImGui::TableSetColumnIndex(column) && column > 0)
                            continue;
                        else FillTable1(row, column, base_d, base_e, (p - 25) / 10);
                    }
                }
                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Detailed Tables")) {
            ImGui::Text("apply settings from other window to fill in the tables");
            if (s1 > 0) {
                ImGui::Text("r1 is the total remaining slots from row 1");
                ImGui::Text("r2 is the total remaining slots from row 2");
                ImGui::Text("r3 is the total remaining slots from row 3");
                ImGui::ColorButton("##ColorButton2", ImVec4(0.3f, 0.3f, 0.7f, 0.65f), flags2);
                ImGui::SameLine();
                ImGui::Text("means row 1 is chosen and");
                ImGui::SameLine();
                ImGui::ColorButton("##ColorButton3", ImVec4(0.3f, 0.7f, 0.3f, 0.65f), flags2);
                ImGui::SameLine();
                ImGui::Text("means row 2 is chosen");
                ImGui::ColorButton("##ColorButton4", ImVec4(0.7f, 0.7f, 0.3f, 0.65f), flags2);
                ImGui::SameLine();
                ImGui::Text("means row 1 or row 2 is chosen");
                ImGui::ColorButton("##ColorButton5", ImVec4(0.7f, 0.3f, 0.3f, 0.65f), flags2);
                ImGui::SameLine();
                ImGui::Text("means row 3 is chosen");
                if (ImGui::Button("Rate##2"))
                    ImGui::OpenPopup("my_select_popup##2");
                ImGui::SameLine();
                ImGui::Text("%d%%", p);
                if (ImGui::BeginPopup("my_select_popup##2")) {
                    for (int i = 0; i < 6; i++) {
                        char buf[32];
                        sprintf(buf, "%d%%", 25 + 10 * i);
                        if (ImGui::Selectable(buf)) {
                            p = 25 + 10 * i;
                            calc_done = false;
                            for (size_t j = 0; j < 1100; j++)
                                table_mem[j] = -1;
                        }
                    }
                    ImGui::EndPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 1 Successes"))
                    ImGui::OpenPopup("my_select_popup##3");
                ImGui::SameLine();
                if (pickr1) {
                    ImGui::Text("%d", r1st);
                    if (ImGui::BeginPopup("my_select_popup##3")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r1st = i;
                                calc_done = false;
                                for (size_t j = 0; j < 1100; j++)
                                    table_mem[j] = -1;
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                else {
                    ImGui::Text("%d", r2st);
                    if (ImGui::BeginPopup("my_select_popup##3")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r2st = i;
                                calc_done = false;
                                for (size_t j = 0; j < 1100; j++)
                                    table_mem[j] = -1;
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 2 Successes"))
                    ImGui::OpenPopup("my_select_popup##4");
                ImGui::SameLine();
                if (pickr1) {
                    ImGui::Text("%d", r2st);
                    if (ImGui::BeginPopup("my_select_popup##4")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r2st = i;
                                calc_done = false;
                                for (size_t j = 0; j < 1100; j++)
                                    table_mem[j] = -1;
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                else {
                    ImGui::Text("%d", r1st);
                    if (ImGui::BeginPopup("my_select_popup##4")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r1st = i;
                                calc_done = false;
                                for (size_t j = 0; j < 1100; j++)
                                    table_mem[j] = -1;
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 3 Successes"))
                    ImGui::OpenPopup("my_select_popup##9");
                ImGui::SameLine();
                ImGui::Text("%d", r3st);
                if (ImGui::BeginPopup("my_select_popup##9")) {
                    for (int i = 0; i < smax - 1; i++) {
                        char buf[32];
                        sprintf(buf, "%d", i);
                        if (ImGui::Selectable(buf)) {
                            r3st = i;
                            calc_done = false;
                            for (size_t j = 0; j < 1100; j++)
                                table_mem[j] = -1;
                        }
                    }
                    ImGui::EndPopup();
                }
                for (size_t z = 11; z-- > 0; ) {
                    if (smax - 1 < z)
                        continue;
                    ImGui::Text("Table %u: Expected value for chosen row given r1 vs r2 where r3 = %u", smax - z, z);
                    std::string s3 = "##Table_" + std::to_string(z);
                    char* buf2 = &s3[0];
                    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 14); //rows + 2 + new lines, and the +2 comes from row 1 labels and scroll bar
                    if (ImGui::BeginTable(buf2, 11, flags, outer_size)) {
                        ImGui::TableSetupScrollFreeze(1, 1);
                        ImGui::TableSetupColumn("\\r1\n \\ \nr2\\", ImGuiTableColumnFlags_NoHide);
                        for (size_t i = 0; i < 10; i++) {
                            std::string s = "\n" + std::to_string(i + 1);
                            char* buf = &s[0];
                            ImGui::TableSetupColumn(buf);
                        }
                        ImGui::TableHeadersRow();
                        for (size_t row = 0; row < 10; row++) {
                            ImGui::TableNextRow();
                            ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.3f, 0.3f, 0.65f));
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + 1, row_bg_color);
                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("%d", row + 1);
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.19f, 0.19f, 0.2f, 1.0f)));
                            for (size_t column = 1; column < 11; column++) {
                                if (!ImGui::TableSetColumnIndex(column) && column > 0)
                                    continue;
                                else if (smax - 1 < row + 1 || smax - 1 < column || (pickr1 && (r2st >= smax - row - 1 || r1st >= smax - column)) || (!pickr1 && (r1st >= smax - row - 1 || r2st >= smax - column))) {
                                    ImGui::Text("n/a");
                                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.19f, 0.19f, 0.2f, 1.0f)));
                                }
                                else FillTable2(row, column, z, smax, r1st, r2st, r3st, calc_done, p_m, sacrifice, pickr1, base_e, dt, exp, prob_t, (p - 25) / 10, table_mem);
                                if (z == 0 && row == 9 && column == 10)
                                    calc_done = true;
                            }
                        }
                        ImGui::EndTable();
                    }
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Probability Tables")) {
            ImGui::Text("apply settings from other window to fill in the tables");
            if (p_m && s1 > 0) {
                ImGui::Text("r1 is the total remaining slots from row 1");
                ImGui::Text("r2 is the total remaining slots from row 2");
                ImGui::Text("r3 is the total remaining slots from row 3");
                if (ImGui::Button("Rate##3"))
                    ImGui::OpenPopup("my_select_popup##5");
                ImGui::SameLine();
                ImGui::Text("%d%%", p);
                if (ImGui::BeginPopup("my_select_popup##5")) {
                    for (int i = 0; i < 6; i++) {
                        char buf[32];
                        sprintf(buf, "%d%%", 25 + 10 * i);
                        if (ImGui::Selectable(buf)) {
                            p = 25 + 10 * i;
                            calc_done2 = false;
                            for (size_t j = 0; j < 1100; j++) {
                                table_mem3[j] = -1;
                                table_mem2[j] = -1;
                            }
                        }
                    }
                    ImGui::EndPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 1 Successes##1"))
                    ImGui::OpenPopup("my_select_popup##6");
                ImGui::SameLine();
                if (pickr1) {
                    ImGui::Text("%d", r1st);
                    if (ImGui::BeginPopup("my_select_popup##6")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r1st = i;
                                calc_done2 = false;
                                for (size_t j = 0; j < 1100; j++) {
                                    table_mem3[j] = -1;
                                    table_mem2[j] = -1;
                                }
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                else {
                    ImGui::Text("%d", r2st);
                    if (ImGui::BeginPopup("my_select_popup##6")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r2st = i;
                                calc_done2 = false;
                                for (size_t j = 0; j < 1100; j++) {
                                    table_mem3[j] = -1;
                                    table_mem2[j] = -1;
                                }
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 2 Successes##1"))
                    ImGui::OpenPopup("my_select_popup##7");
                ImGui::SameLine();
                if (pickr1) {
                    ImGui::Text("%d", r2st);
                    if (ImGui::BeginPopup("my_select_popup##7")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r2st = i;
                                calc_done2 = false;
                                for (size_t j = 0; j < 1100; j++) {
                                    table_mem3[j] = -1;
                                    table_mem2[j] = -1;
                                }
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                else {
                    ImGui::Text("%d", r1st);
                    if (ImGui::BeginPopup("my_select_popup##7")) {
                        for (int i = 0; i < smax - 1; i++) {
                            char buf[32];
                            sprintf(buf, "%d", i);
                            if (ImGui::Selectable(buf)) {
                                r1st = i;
                                calc_done2 = false;
                                for (size_t j = 0; j < 1100; j++) {
                                    table_mem3[j] = -1;
                                    table_mem2[j] = -1;
                                }
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Row 3 Successes"))
                    ImGui::OpenPopup("my_select_popup##8");
                ImGui::SameLine();
                ImGui::Text("%d", r3st);
                if (ImGui::BeginPopup("my_select_popup##8")) {
                    for (int i = 0; i < smax - 1; i++) {
                        char buf[32];
                        sprintf(buf, "%d", i);
                        if (ImGui::Selectable(buf)) {
                            r3st = i;
                            calc_done2 = false;
                            for (size_t j = 0; j < 1100; j++) {
                                table_mem3[j] = -1;
                                table_mem2[j] = -1;
                            }
                        }
                    }
                    ImGui::EndPopup();
                }
                ImGui::Text("P(row 1 >=");
                ImGui::SameLine();
                ImGui::PushItemWidth(25.0f);
                if (pickr1) {
                    if (ImGui::InputScalar("##7", ImGuiDataType_U8, &r1pt, NULL, NULL, "%u")) {
                        if (r1pt < 0)
                            r1pt = 0;
                        else if (r1pt > smax - 1)
                            r1pt = smax - 1;
                        calc_done2 = false;
                        for (size_t j = 0; j < 1100; j++) {
                            table_mem3[j] = -1;
                            table_mem2[j] = -1;
                        }
                    }
                    ImGui::SameLine();
                    ImGui::Text("row 2 >=");
                    ImGui::SameLine();
                    if (ImGui::InputScalar("##8", ImGuiDataType_U8, &r2pt, NULL, NULL, "%u")) {
                        if (r2pt < 0)
                            r2pt = 0;
                        else if (r2pt > smax - 1)
                            r2pt = smax - 1;
                        calc_done2 = false;
                        for (size_t j = 0; j < 1100; j++) {
                            table_mem3[j] = -1;
                            table_mem2[j] = -1;
                        }
                    }
                }
                else {
                    if (ImGui::InputScalar("##7", ImGuiDataType_U8, &r2pt, NULL, NULL, "%u")) {
                        if (r2pt < 0)
                            r2pt = 0;
                        else if (r2pt > smax - 1)
                            r2pt = smax - 1;
                        calc_done2 = false;
                        for (size_t j = 0; j < 1100; j++) {
                            table_mem3[j] = -1;
                            table_mem2[j] = -1;
                        }
                    }
                    ImGui::SameLine();
                    ImGui::Text("row 2 >=");
                    ImGui::SameLine();
                    if (ImGui::InputScalar("##8", ImGuiDataType_U8, &r1pt, NULL, NULL, "%u")) {
                        if (r1pt < 0)
                            r1pt = 0;
                        else if (r1pt > smax - 1)
                            r1pt = smax - 1;
                        calc_done2 = false;
                        for (size_t j = 0; j < 1100; j++) {
                            table_mem3[j] = -1;
                            table_mem2[j] = -1;
                        }
                    }
                }
                ImGui::SameLine();
                ImGui::Text("row 3 <=");
                ImGui::SameLine();
                if (ImGui::InputScalar("##9", ImGuiDataType_U8, &r3pt, NULL, NULL, "%u")) {
                    if (r3pt < 0)
                        r3pt = 0;
                    else if (r3pt > smax - 1)
                        r3pt = smax - 1;
                    calc_done2 = false;
                    for (size_t j = 0; j < 1100; j++) {
                        table_mem3[j] = -1;
                        table_mem2[j] = -1;
                    }
                }
                ImGui::Text("P(row 1 + row 2 >=");
                ImGui::SameLine();
                ImGui::PushItemWidth(25.0f);
                if (ImGui::InputScalar("##10", ImGuiDataType_U8, &r12pt, NULL, NULL, "%u")) {
                    if (r12pt < 0)
                        r12pt = 0;
                    else if (r12pt > 2 * smax - 2)
                        r12pt = 2 * smax - 2;
                    calc_done2 = false;
                    for (size_t j = 0; j < 1100; j++) {
                        table_mem3[j] = -1;
                        table_mem2[j] = -1;
                    }
                }
                ImGui::SameLine();
                ImGui::Text("row 3 <=");
                ImGui::SameLine();
                if (ImGui::InputScalar("##11", ImGuiDataType_U8, &r4pt, NULL, NULL, "%u")) {
                    if (r4pt < 0)
                        r4pt = 0;
                    else if (r4pt > smax - 1)
                        r4pt = smax - 1;
                    calc_done2 = false;
                    for (size_t j = 0; j < 1100; j++) {
                        table_mem3[j] = -1;
                        table_mem2[j] = -1;
                    }
                }
                for (size_t z = 11; z-- > 0; ) {
                    if (smax - 1 < z)
                        continue;
                    ImGui::Text("Table %u: Probabilities given r1 vs r2 where r3 = %u", smax - z, z);
                    std::string s3 = "##Table" + std::to_string(z);
                    char* buf2 = &s3[0];
                    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 21); //rows + 2 + new lines, and the +2 comes from row 1 labels and scroll bar
                    if (ImGui::BeginTable(buf2, 11, flags, outer_size)) {
                        ImGui::TableSetupScrollFreeze(1, 1);
                        ImGui::TableSetupColumn("\\r1\n \\ \nr2\\", ImGuiTableColumnFlags_NoHide);
                        for (size_t i = 0; i < 10; i++) {
                            std::string s = "\n" + std::to_string(i + 1);
                            char* buf = &s[0];
                            ImGui::TableSetupColumn(buf);
                        }
                        ImGui::TableHeadersRow();
                        for (size_t row = 0; row < 10; row++) {
                            ImGui::TableNextRow();
                            ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.7f, 0.3f, 0.3f, 0.65f));
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + 1, row_bg_color);
                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("%d", row + 1);
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.19f, 0.19f, 0.2f, 1.0f)));
                            for (size_t column = 1; column < 11; column++) {
                                if (!ImGui::TableSetColumnIndex(column) && column > 0)
                                    continue;
                                else if (smax - 1 < row + 1 || smax - 1 < column || (pickr1 && (r2st >= smax - 1 - row || r1st >= smax - column)) || (!pickr1 && (r1st >= smax - 1 - row || r2st >= smax - column))) {
                                    ImGui::Text("n/a\nn/a");
                                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.19f, 0.19f, 0.2f, 1.0f)));
                                }
                                else FillTable3(row, column, z, smax, r1st, r2st, r3st, r1pt, r2pt, r3pt, r12pt, r4pt, calc_done2, pickr1, dt, prob_t, (p - 25) / 10, table_mem2, table_mem3);
                                if (z == 0 && row == 9 && column == 10)
                                    calc_done2 = true;
                            }
                        }
                        ImGui::EndTable();
                    }
                }
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

#if BUILD_PLATFORM == WINDOWS_BUILD
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ability Stone Calculator", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
        throw("Unable to context to OpenGL");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    //See header file Calculator.h for general descriptions of each function and variable
    //Certain variables used in applied settings will have 'a' at the end such as pickr1 to pickr1a
    //Certain variables used in table window will have 't' at the end
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    bool pickr1 = true, pickr2 = false, p_m = false, c_m = false, init = false, init2 = false, options = true, enable_p = false, calc_done = false, sacrifice = false, sacrificea = false;
    bool r1sh[10]{}, r2sh[10]{}, r3sh[10]{}, show_table = false, p_ma = false, pickr1a = true, c_ma = false, psc = false, calc_cm = false, calc_pm = false, calc_done2 = false, calc_sac = false;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;
    ImGuiWindowFlags window_flags2 = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
    int p = 75, choice = 0, p2 = 45;
    size_t start1 = 0, start2 = 0, smax = 11, r1s = 0, r2s = 0, r3s = 0, row1 = 0, row2 = 0, row3 = 0, r1c = 0, r2c = 0, r3c = 0, r12pt = 0, r4pt = 0;
    size_t r1p = 0, r2p = 0, r3p = 0, r12p = 0, r4p = 0, r1st = 0, r2st = 0, r3st = 0, smaxa = 0, s1a = 0, s1 = 10, r1pt = 0, r2pt = 0, r3pt = 0;
    int hist[31]{};
    long double w1 = 0.5, w2 = 0.5, r1e = 0, r2e = 0, r3e = 0, prob = 0, prob2 = 0, w2a = 0;
    float sz2 = 1.0f, x = 0.0f, y = 0.0f, progress = 0.0f, dyd = 51.0f, dxd = 0.0f, f1 = 0.5f;
    const float sz = 48.0f, spacing = 10.0f;
    long double base_e[6][231]; //base expected value table
    bool base_d[6][200]{}; //base decision tables
    std::vector<std::vector<int>> d25, d35, d45, d55, d65, d75; //decision tables
    std::vector<std::vector<std::vector<int>>> dt; //will store d25 to d75
    std::vector<std::vector<std::vector<long double>>> e25, e35, e45, e55, e65, e75; //expected values
    std::vector<std::vector<std::vector<std::vector<long double>>>> exp; //will store e25 to e75
    std::vector<std::vector<std::vector<long double>>> p25, p35, p45, p55, p65, p75; //probabilities
    std::vector<std::vector<std::vector<std::vector<long double>>>> prob_t; //will store p25 to p75
    std::vector<long double> table_mem(1100, -1); //tables used for Tables window and used to avoid recalculations
    std::vector<long double> table_mem2(1100, -1);
    std::vector<long double> table_mem3(1100, -1);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (init && calc_cm == calc_pm && calc_cm == calc_sac)
                    ImGui::MenuItem("Show Tables", NULL, &show_table);
                if (ImGui::MenuItem("Quit"))
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        if (calc_sac) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
            if (ImGui::Begin("calculating3", NULL, window_flags2)) {
                if (progress == 0.0f) {
                    initcalcTable2(smax, base_d, dt, exp, prob_t);
                    progress = 0.01f;
                }
                else {
                    calcTable3(start1, start2, r1c, r2c, r3c, smax, base_d, w1, dt, exp, prob_t);
                    start2++;
                    if (start2 == smax) {
                        start2 = 1;
                        start1++;
                        if (start1 == smax) {
                            calc_sac = false;
                            start2 = 1;
                            choice = dt[5][(smax * smax + smax + 1) * s1][0];
                            r1e = exp[5][(smax * smax + smax + 1) * s1][0][0];
                            r3e = expr3((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
                            r2e = expr2((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
                            func11(r12p, r4p, prob2, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            func12(r3p, r1p, r2p, prob, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            smaxa = smax;
                            s1a = s1;
                            p_ma = p_m;
                            pickr1a = pickr1;
                            w2a = w2;
                            c_ma = c_m;
                            sacrificea = sacrifice;
                        }
                    }
                    progress += 0.99f / (static_cast<float>(smax * (smax - 1)));
                }
                ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Text("calculating");
                if (start1 == smax) {
                    start1 = 0;
                    progress = 0.0f;
                }
            }
            ImGui::End();
        }
        else if (calc_cm) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
            if (ImGui::Begin("calculating", NULL, window_flags2)) {
                if (progress == 0.0f) {
                    initcalcTable2(smax, base_d, dt, exp, prob_t);
                    progress = 0.01f;
                }
                else {
                    calcTable2(start1, start2, r1c, r2c, smax, base_d, w1, dt, exp, prob_t);
                    start2++;
                    if (start2 == smax) {
                        start2 = 1;
                        start1++;
                        if (start1 == smax) {
                            calc_cm = false;
                            start2 = 1;
                            choice = dt[5][(smax * smax + smax + 1) * s1][0];
                            r1e = exp[5][(smax * smax + smax + 1) * s1][0][0];
                            r3e = base_e[5][23 * s1];
                            r2e = expr2((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
                            func11(r12p, r4p, prob2, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            func12(r3p, r1p, r2p, prob, (smax * smax + smax + 1) * s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            smaxa = smax;
                            s1a = s1;
                            p_ma = p_m;
                            pickr1a = pickr1;
                            w2a = w2;
                            c_ma = c_m;
                            sacrificea = sacrifice;
                        }
                    }
                    progress += 0.99f / (static_cast<float>(smax * (smax - 1)));
                }
                ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Text("calculating");
                if (start1 == smax) {
                    start1 = 0;
                    progress = 0.0f;
                }
            }
            ImGui::End();
        }
        else if (calc_pm) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
            if (ImGui::Begin("calculating2", NULL, window_flags2)) {
                if (progress == 0.0f) {
                    initcalcProbabilities(smax, base_d, prob_t);
                    progress = 0.01f;
                }
                else {
                    calcProbabilities(start1, start2, smax, dt, prob_t);
                    start2++;
                    if (start2 == smax) {
                        start2 = 1;
                        start1++;
                        if (start1 == smax) {
                            calc_pm = false;
                            start2 = 1;
                            choice = dt[5][(smax * smax + smax + 1) * s1][0];
                            r1e = exp[5][(smax * smax + smax + 1) * s1][0][0];
                            r3e = base_e[5][23 * s1];
                            r2e = expr2((smax * smax + smax + 1) * s1, 0, s1, s1, s1, 0, 0, 0, prob_t, 5);
                            func11(r12p, r4p, prob2, (smax* smax + smax + 1)* s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            func12(r3p, r1p, r2p, prob, (smax* smax + smax + 1)* s1, 0, s1, s1, s1, r1s, r2s, r3s, prob_t, 5);
                            smaxa = smax;
                            s1a = s1;
                            p_ma = p_m;
                            pickr1a = pickr1;
                            w2a = w2;
                            c_ma = c_m;
                            sacrificea = sacrifice;
                        }
                    }
                    progress += 0.99f / (static_cast<float>(smax * (smax - 1)));
                }
                ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Text("calculating");
                if (start1 == smax) {
                    start1 = 0;
                    progress = 0.0f;
                }
            }
            ImGui::End();
        }
        else if (options) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
            ImGui::Begin("Memory Options", NULL, window_flags);
            ImGui::Text("Disable probability mode to use less memory?");
            if (ImGui::Button("Yes"))
                options = false;
            ImGui::SameLine();
            ImGui::Text("(less than 70 MB of RAM)");
            if (ImGui::Button("No")) {
                enable_p = true;
                options = false;
            }
            ImGui::SameLine();
            ImGui::Text("(about 3.5 GB of RAM)");
            ImGui::End();
        }
        else if (init && calc_cm == calc_pm && calc_cm == calc_sac) {
            if (show_table)
                ShowTables(&show_table, p_ma, sacrificea, pickr1a, calc_done, calc_done2, s1a, smaxa, p2, r1st, r2st, r3st, r1pt, r2pt, r3pt, r12pt, r4pt, base_e, base_d, dt, exp, prob_t, table_mem, table_mem2, table_mem3);
            ImGui::SetNextWindowSize(ImVec2(789, 466), ImGuiCond_FirstUseEver);
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
            ImGui::Begin("Ability Stone Calculator", NULL, window_flags);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImGui::Text("Configure the settings for probability mode, weight of row 1, pick row x in a tie, and slots per row.");
            ImGui::Text("Each time you are done changing these settings, click apply settings.");
            ImGui::PushItemWidth(70.f);
            if (enable_p) {
                if (ImGui::Checkbox("probability mode", &p_m)) {
                    p_m ? smax = s1 + 1 : smax = 11;
                    if (p_m)
                        smax = s1 + 1;
                    else {
                        smax = 11;
                        r1p = 0;
                        r2p = 0;
                        r3p = 0;
                        r12p = 0;
                        r4p = 0;
                        r1c = 0;
                        r2c = 0;
                        r3c = 0;
                    }
                }
                ImGui::SameLine();
                HelpMarker("Load times increase as slots increase.");
                ImGui::SameLine();
            }
            if (ImGui::Button("apply settings")) {
                r1s = 0; r2s = 0; r3s = 0; row1 = 0; row2 = 0; row3 = 0; p = 75; calc_done = false, calc_done2 = false;
                for (size_t i = 0; i < 31; i++)
                    hist[i] = 0;
                for (size_t i = 0; i < 1100; i++) {
                    table_mem[i] = -1;
                    table_mem2[i] = -1;
                    table_mem3[i] = -1;
                }
                for (size_t i = 0; i < 10; i++) {
                    r1sh[i] = false;
                    r2sh[i] = false;
                    r3sh[i] = false;
                }
                if (p_m) {
                    smax = s1 + 1;
                    if (c_m) {
                        sacrifice ? calc_sac = true : calc_cm = true;
                    }
                    else {
                        calc_pm = true;
                        calcTable(smax, base_d, w1, dt, exp);
                    }
                }
                else {
                    calcTable(smax, base_d, w1, dt, exp);
                    choice = dt[5][(smax * smax + smax + 1) * s1][0];
                    r1e = exp[5][(smax * smax + smax + 1) * s1][0][0];
                    r3e = base_e[5][23 * s1];
                    r2e = exp[5][(smax * smax + smax + 1) * s1][0][1];
                    smaxa = smax;
                    s1a = s1;
                    p_ma = p_m;
                    pickr1a = pickr1;
                    w2a = w2;
                    c_ma = c_m;
                    sacrificea = sacrifice;
                }
            }
            if (p_m) {
                ImGui::SameLine();
                if (ImGui::Checkbox("enable conditions on row 1 and row 2", &c_m)) {
                    if (!c_m) {
                        r1c = 0;
                        r2c = 0;
                        r3c = 0;
                    }
                }
                ImGui::SameLine();
                HelpMarker("Weights are used after conditions are met.");
            }
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(200.f);
            if (ImGui::SliderFloat("weight of row 1", &f1, 0.0f, 1.0f)) {
                w2 = static_cast<long double>(f1);
                if (w2 < 0)
                    w2 = 0;
                else if (w2 > 1)
                    w2 = 1;
                pickr1 ? w1 = w2 : w1 = 1 - w2;
            }
            ImGui::SameLine();
            HelpMarker("Slide to value or Ctrl+left click to enter a value.\nWeight of row 2 is 1 minus this value.");
            if (p_m && c_m) {
                ImGui::SameLine();
                if (ImGui::Checkbox("increase probability by sacrificing expected values", &sacrifice)) {
                    if (!sacrifice) {
                        r1c = 0;
                        r2c = 0;
                        r3c = 0;
                    }
                }
                ImGui::SameLine();
                HelpMarker("Increases probability of satisfying the inequalties by decreasing the expected values for successes in row 1 and row 2, which increases the expected value for successes in row 3. This is good if you will not use stones that don't meet the conditions.");
            }
            if (ImGui::Button("slots per row"))
                ImGui::OpenPopup("my_select_popup1");
            ImGui::SameLine();
            ImGui::Text("%u", s1);
            ImGui::SameLine();
            HelpMarker("If only reducing the amount of slots with probability mode, then there is no need to apply settings.\nIf only changing the amount of slots without probability mode, then there is no need to apply settings.");
            if (ImGui::BeginPopup("my_select_popup1")) {
                for (int i = 1; i < 11; i++) {
                    char buf[32];
                    sprintf(buf, "%u", i);
                    if (ImGui::Selectable(buf)) {
                        s1 = i;
                        if (s1a > 0) {
                            if (p_ma) {
                                if (r1p > s1)
                                    r1p = s1;
                                if (r2p > s1)
                                    r2p = s1;
                                if (r3p > s1)
                                    r3p = s1;
                                if (r12p > 2 * s1)
                                    r12p = 2 * s1;
                                if (r4p > s1)
                                    r4p = s1;
                                if (c_m) {
                                    if (r1c > s1)
                                        r1c = s1;
                                    if (r2c > s1)
                                        r2c = s1;
                                    if (sacrifice && r3c > s1)
                                        r3c = s1;
                                }
                                if (s1 <= s1a && row1 <= s1 && row2 <= s1 && row3 <= s1) {
                                    psc = true; //this variable is only true under these conditions, which is used to avoid recalculation
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                }
                                else {
                                    psc = false;
                                    PerformReset(hist, smaxa, s1a, pickr1a, p_ma, sacrificea, prob, prob2, r1p, r2p, r3p, r12p, r4p, r1s, r2s, r3s, row1, row2, row3, p, r1sh, r2sh, r3sh, choice, r1e, r2e, r3e, base_e, dt, exp, prob_t);
                                }
                            }
                            else if (row1 > s1 || row2 > s1 || row3 > s1) {
                                psc = false;
                                PerformReset(hist, smaxa, s1a, pickr1a, p_ma, sacrificea, prob, prob2, r1p, r2p, r3p, r12p, r4p, r1s, r2s, r3s, row1, row2, row3, p, r1sh, r2sh, r3sh, choice, r1e, r2e, r3e, base_e, dt, exp, prob_t);
                            }
                            else {
                                psc = false;
                                update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                        }
                    }
                }
                ImGui::EndPopup();
            }
            if (ImGui::Button("Reset")) {
                if (p_ma) {
                    if (psc)
                        PerformReset(hist, smaxa, s1, pickr1a, p_ma, sacrificea, prob, prob2, r1p, r2p, r3p, r12p, r4p, r1s, r2s, r3s, row1, row2, row3, p, r1sh, r2sh, r3sh, choice, r1e, r2e, r3e, base_e, dt, exp, prob_t);
                    else PerformReset(hist, smaxa, s1a, pickr1a, p_ma, sacrificea, prob, prob2, r1p, r2p, r3p, r12p, r4p, r1s, r2s, r3s, row1, row2, row3, p, r1sh, r2sh, r3sh, choice, r1e, r2e, r3e, base_e, dt, exp, prob_t);
                }
                else PerformReset(hist, smaxa, s1, pickr1a, p_ma, sacrificea, prob, prob2, r1p, r2p, r3p, r12p, r4p, r1s, r2s, r3s, row1, row2, row3, p, r1sh, r2sh, r3sh, choice, r1e, r2e, r3e, base_e, dt, exp, prob_t);
            }
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Dummy(ImVec2(200.0f, 0.0f));
            ImGui::SameLine();
            if (ImGui::Button("Undo")) {
                //10 = row 1 fail, 11 = row 1 success, 12 = row 1 fail at p = 75, 13 = row 1 success at p = 25
                //20 = row 2 fail, 21 = row 2 success, 22 = row 2 fail at p = 75, 23 = row 2 success at p = 25
                //30 = row 3 fail, 31 = row 3 success, 32 = row 3 fail at p = 75, 33 = row 3 success at p = 25
                if (hist[0] > 0) {
                    if (hist[hist[0]] == 10 || hist[hist[0]] == 12) {
                        r1sh[--row1] = false;
                        if (p > 25 && !(p == 75 && hist[hist[0]] % 10 == 2))
                            p -= 10;
                    }
                    else if (hist[hist[0]] == 11 || hist[hist[0]] == 13) {
                        r1sh[--row1] = false;
                        r1s--;
                        if (p < 75 && !(p == 25 && hist[hist[0]] % 10 == 3))
                            p += 10;
                    }
                    else if (hist[hist[0]] == 20 || hist[hist[0]] == 22) {
                        r2sh[--row2] = false;
                        if (p > 25 && !(p == 75 && hist[hist[0]] % 10 == 2))
                            p -= 10;
                    }
                    else if (hist[hist[0]] == 21 || hist[hist[0]] == 23) {
                        r2sh[--row2] = false;
                        r2s--;
                        if (p < 75 && !(p == 25 && hist[hist[0]] % 10 == 3))
                            p += 10;
                    }
                    else if (hist[hist[0]] == 30 || hist[hist[0]] == 32) {
                        r3sh[--row3] = false;
                        if (p > 25 && !(p == 75 && hist[hist[0]] % 10 == 2))
                            p -= 10;
                    }
                    else {
                        r3sh[--row3] = false;
                        r3s--;
                        if (p < 75 && !(p == 25 && hist[hist[0]] % 10 == 3))
                            p += 10;
                    }
                    hist[0]--;
                    if (p_ma) {
                        if (psc)
                            update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                    }
                    else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                }
            }
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Dummy(ImVec2(200.0f, 0.0f));
            ImGui::SameLine();
            if (ImGui::Button("Rate"))
                ImGui::OpenPopup("my_select_popup");
            ImGui::SameLine();
            ImGui::Text("%d%%", p);
            if (ImGui::BeginPopup("my_select_popup")) {
                for (int i = 0; i < 6; i++) {
                    char buf[32];
                    sprintf(buf, "%d%%", 25 + 10 * i);
                    if (ImGui::Selectable(buf)) {
                        p = 25 + 10 * i;
                        if (s1a > 0) {
                            if (p_ma) {
                                if (psc)
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                            else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        }
                    }
                }
                ImGui::EndPopup();
            }
            const ImVec2 screen_p = ImGui::GetCursorScreenPos();
            x = screen_p.x + 4.0f;
            y = screen_p.y + 4.0f;
            sz2 += 16.0f * ImGui::GetIO().DeltaTime;
            if (sz2 > 23.0f)
                sz2 = 1.0f;
            ImGui::PopItemWidth();
            ImGui::PushItemWidth(25.0f);
            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            for (int n = 0; n < 2; n++) {
                draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz + 9 * (sz + spacing), y + sz / 2 - 2.0f), ImColor(30, 40, 55, 255));
                x += 515.0f;
                draw_list->AddNgonFilled(ImVec2(x + sz * 0.20f, y + sz * 0.20f), sz * 0.20f, ImColor(1, 151, 213, 255), 4);
                x = screen_p.x + 4.0f;
                y += sz / 2 - 2.0f;
                draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz + 9 * (sz + spacing), y + sz + 4.0f), ImColor(0, 0, 0, 255));
                y += 2.0f;
                x += 2.0f;
                if (pickr1a) {
                    for (size_t m = 0; m < s1; m++) {
                        if (n == 0 && m < row1) {
                            if (r1sh[m])
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4);
                            else draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(66, 77, 82, 255), 4);
                        }
                        else if (n == 1 && m < row2) {
                            if (r2sh[m])
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4);
                            else draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(66, 77, 82, 255), 4);
                        }
                        else {
                            if (((m == row1 && (choice == 0 || choice == 3)) || (m == row2 && choice == 1)) && (n == choice || n == choice - 3))
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz2, ImColor(0, 255, 0, 255), 4);
                            draw_list->AddNgon(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4, 3.0f);
                        }
                        x += sz + spacing - 0.4f;
                    }
                }
                else {
                    for (size_t m = 0; m < s1; m++) {
                        if (n == 0 && m < row2) {
                            if (r2sh[m])
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4);
                            else draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(66, 77, 82, 255), 4);
                        }
                        else if (n == 1 && m < row1) {
                            if (r1sh[m])
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4);
                            else draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(66, 77, 82, 255), 4);
                        }
                        else {
                            if (((m == row2 && choice == 1) || (m == row1 && (choice == 0 || choice == 3))) && (n == 1 - choice || n == 4 - choice))
                                draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz2, ImColor(0, 255, 0, 255), 4);
                            draw_list->AddNgon(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(1, 151, 213, 255), 4, 3.0f);
                        }
                        x += sz + spacing - 0.4f;
                    }
                }
                dxd = 0.0f;
                if (p_m && c_m)
                    dyd = 0.0f;
                else dyd = 51.0f;
                if (n == 0) {
                    ImGui::Dummy(ImVec2(0.0f, 0.0f));
                    ImGui::SameLine();
                    if (pickr1a)
                        ImGui::Text("row 1, weight = %f, expected value = %f", w2a, r1e + r1s);
                    else if (p_ma)
                        ImGui::Text("row 1, weight = %f, expected value = %f", w2a, r2e + r2s);
                    else {
                        ImGui::Text("row 1, weight = %f, expected value = %f*", w2a, r2e + r2s);
                        dxd = 7.0f;
                    }
                    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                    ImGui::Dummy(ImVec2(165.0f - dxd, 0.0f));
                    ImGui::SameLine();
                    if (pickr1a)
                        ImGui::Text("x%u", r1s);
                    else ImGui::Text("x%u", r2s);
                    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                    ImGui::Dummy(ImVec2(17.0f, 0.0f));
                    ImGui::SameLine();
                    if (ImGui::Checkbox("pick row 1 in a tie", &pickr1)) {
                        pickr2 = !pickr1;
                        w1 = 1 - w1;
                    }
                    ImGui::Dummy(ImVec2(585.0f, dyd));
                    ImGui::SameLine();
                    if (ImGui::Button("Success")) {
                        if (s1a > 0 && row1 * pickr1a + row2 * !pickr1a < s1) {
                            if (pickr1a) {
                                r1sh[row1++] = true;
                                r1s++;
                                if (hist[0] < 30) {
                                    if (p == 25)
                                        hist[++hist[0]] = 13;
                                    else hist[++hist[0]] = 11;
                                }
                            }
                            else {
                                r2sh[row2++] = true;
                                r2s++;
                                if (hist[0] < 30) {
                                    if (p == 25)
                                        hist[++hist[0]] = 23;
                                    else hist[++hist[0]] = 21;
                                }
                            }
                            if (p != 25)
                                p -= 10;
                            if (p_ma) {
                                if (psc)
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                            else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Fail")) {
                        if (s1a > 0 && row1 * pickr1a + row2 * !pickr1a < s1) {
                            if (pickr1a) {
                                row1++;
                                if (hist[0] < 30) {
                                    if (p == 75)
                                        hist[++hist[0]] = 12;
                                    else hist[++hist[0]] = 10;
                                }
                            }
                            else {
                                row2++;
                                if (hist[0] < 30) {
                                    if (p == 75)
                                        hist[++hist[0]] = 22;
                                    else hist[++hist[0]] = 20;
                                }
                            }
                            if (p != 75)
                                p += 10;
                            if (p_ma) {
                                if (psc)
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                            else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        }
                    }
                    if (p_m && c_m) {
                        ImGui::Dummy(ImVec2(585.0f, 28.0f));
                        ImGui::SameLine();
                        ImGui::Text("row 1 >=");
                        ImGui::SameLine();
                        if (pickr1) {
                            if (ImGui::InputScalar("##", ImGuiDataType_U8, &r1c, NULL, NULL, "%u")) {
                                if (r1c < 0)
                                    r1c = 0;
                                else if (r1c > s1)
                                    r1c = s1;
                            }
                        }
                        else if (ImGui::InputScalar("##", ImGuiDataType_U8, &r2c, NULL, NULL, "%u")) {
                            if (r2c < 0)
                                r2c = 0;
                            else if (r2c > s1)
                                r2c = s1;
                        }
                    }
                }
                else {
                    ImGui::Dummy(ImVec2(0.0f, 0.0f));
                    ImGui::SameLine();
                    if (pickr1a) {
                        if (p_ma)
                            ImGui::Text("row 2, weight = %f, expected value = %f", 1 - w2a, r2e + r2s);
                        else {
                            ImGui::Text("row 2, weight = %f, expected value = %f*", 1 - w2a, r2e + r2s);
                            dxd = 7.0f;
                        }
                    }
                    else ImGui::Text("row 2, weight = %f, expected value = %f", 1 - w2a, r1e + r1s);
                    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                    ImGui::Dummy(ImVec2(165.0f - dxd, 0.0f));
                    ImGui::SameLine();
                    if (pickr1a)
                        ImGui::Text("x%u", r2s);
                    else ImGui::Text("x%u", r1s);
                    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                    ImGui::Dummy(ImVec2(17.0f, 0.0f));
                    ImGui::SameLine();
                    if (ImGui::Checkbox("pick row 2 in a tie", &pickr2)) {
                        pickr1 = !pickr2;
                        w1 = 1 - w1;
                    }
                    ImGui::Dummy(ImVec2(585.0f, dyd));
                    ImGui::SameLine();
                    if (ImGui::Button("Success##")) {
                        if (s1a > 0 && row2 * pickr1a + row1 * !pickr1a < s1) {
                            if (pickr1a) {
                                r2sh[row2++] = true;
                                r2s++;
                                if (hist[0] < 30) {
                                    if (p == 25)
                                        hist[++hist[0]] = 23;
                                    else hist[++hist[0]] = 21;
                                }
                            }
                            else {
                                r1sh[row1++] = true;
                                r1s++;
                                if (hist[0] < 30) {
                                    if (p == 25)
                                        hist[++hist[0]] = 13;
                                    else hist[++hist[0]] = 11;
                                }
                            }
                            if (p != 25)
                                p -= 10;
                            if (p_ma) {
                                if (psc)
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                            else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Fail##")) {
                        if (s1a > 0 && row2 * pickr1a + row1 * !pickr1a < s1) {
                            if (pickr1a) {
                                row2++;
                                if (hist[0] < 30) {
                                    if (p == 75)
                                        hist[++hist[0]] = 22;
                                    else hist[++hist[0]] = 20;
                                }
                            }
                            else {
                                row1++;
                                if (hist[0] < 30) {
                                    if (p == 75)
                                        hist[++hist[0]] = 12;
                                    else hist[++hist[0]] = 10;
                                }
                            }
                            if (p != 75)
                                p += 10;
                            if (p_ma) {
                                if (psc)
                                    update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                                else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                            }
                            else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        }
                    }
                    if (p_m && c_m) {
                        ImGui::Dummy(ImVec2(585.0f, 28.0f));
                        ImGui::SameLine();
                        ImGui::Text("row 2 >=");
                        ImGui::SameLine();
                        if (pickr1) {
                            if (ImGui::InputScalar("##1", ImGuiDataType_U8, &r2c, NULL, NULL, "%u")) {
                                if (r2c < 0)
                                    r2c = 0;
                                else if (r2c > s1)
                                    r2c = s1;
                            }
                        }
                        else if (ImGui::InputScalar("##1", ImGuiDataType_U8, &r1c, NULL, NULL, "%u")) {
                            if (r1c < 0)
                                r1c = 0;
                            else if (r1c > s1)
                                r1c = s1;
                        }
                    }
                }
                x = screen_p.x + 4.0f;
                y += sz + spacing - 4.0f;
            }
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz + 9 * (sz + spacing), y + sz / 2 - 2.0f), ImColor(44, 28, 33, 255));
            x += 515.0f;
            draw_list->AddNgonFilled(ImVec2(x + sz * 0.20f, y + sz * 0.20f), sz * 0.20f, ImColor(179, 70, 65, 255), 4);
            x = screen_p.x + 4.0f;
            ImGui::Dummy(ImVec2(0.0f, 16.0f));
            ImGui::SameLine();
            ImGui::Text("row 3                     expected value = %f", r3e + r3s);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Dummy(ImVec2(165.0f, 0.0f));
            ImGui::SameLine();
            ImGui::Text("x%u", r3s);
            if (p_m && c_m && sacrifice)
                ImGui::Dummy(ImVec2(585.0f, 0.0f));
            else ImGui::Dummy(ImVec2(585.0f, 52.0f));
            ImGui::SameLine();
            if (ImGui::Button("Success##1")) {
                if (s1a > 0 && row3 < s1) {
                    r3sh[row3++] = true;
                    r3s++;
                    if (hist[0] < 30) {
                        if (p == 25)
                            hist[++hist[0]] = 33;
                        else hist[++hist[0]] = 31;
                    }
                    if (p != 25)
                        p -= 10;
                    if (p_ma) {
                        if (psc)
                            update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                    }
                    else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Fail##1")) {
                if (s1a > 0 && row3 < s1) {
                    row3++;
                    if (hist[0] < 30) {
                        if (p == 75)
                            hist[++hist[0]] = 32;
                        else hist[++hist[0]] = 30;
                    }
                    if (p != 75)
                        p += 10;
                    if (p_ma) {
                        if (psc)
                            update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                        else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1a, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                    }
                    else update_changes(prob, prob2, r1p, r2p, r3p, r12p, r4p, smaxa, p, choice, s1, row3, r1s, r2s, r3s, row1, row2, r1e, r2e, r3e, p_ma, sacrificea, base_e, dt, exp, prob_t);
                }
            }
            if (p_m && c_m && sacrifice) {
                ImGui::Dummy(ImVec2(585.0f, 29.0f));
                ImGui::SameLine();
                ImGui::Text("row 3 <=");
                ImGui::SameLine();
                if (ImGui::InputScalar("##7", ImGuiDataType_U8, &r3c, NULL, NULL, "%u")) {
                    if (r3c < 0)
                        r3c = 0;
                    else if (r3c > s1)
                        r3c = s1;
                }
            }
            y += sz / 2 - 2.0f;
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz + 9 * (sz + spacing), y + sz + 4.0f), ImColor(0, 0, 0, 255));
            y += 2.0f;
            x += 2.0f;
            for (size_t n = 0; n < s1; n++) {
                if (n < row3) {
                    if (r3sh[n])
                        draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(179, 70, 65, 255), 4);
                    else draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(66, 77, 82, 255), 4);
                }
                else {
                    if (n == row3 && choice == 2)
                        draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz2, ImColor(0, 255, 0, 255), 4);
                    draw_list->AddNgon(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, ImColor(179, 70, 65, 255), 4, 3.0f);
                } 
                x += sz + spacing - 0.4f;
            }
            ImGui::PopItemWidth();
            if (p_m) {
                ImGui::Text("P(row 1 >=");
                ImGui::SameLine();
                ImGui::PushItemWidth(25.0f);
                if (pickr1) {
                    if (ImGui::InputScalar("##2", ImGuiDataType_U8, &r1p, NULL, NULL, "%u")) {
                        if (r1p < 0)
                            r1p = 0;
                        else if (r1p > s1)
                            r1p = s1;
                    }
                    ImGui::SameLine();
                    ImGui::Text("row 2 >=");
                    ImGui::SameLine();
                    if (ImGui::InputScalar("##3", ImGuiDataType_U8, &r2p, NULL, NULL, "%u")) {
                        if (r2p < 0)
                            r2p = 0;
                        else if (r2p > s1)
                            r2p = s1;
                    }
                }
                else {
                    if (ImGui::InputScalar("##2", ImGuiDataType_U8, &r2p, NULL, NULL, "%u")) {
                        if (r2p < 0)
                            r2p = 0;
                        else if (r2p > s1)
                            r2p = s1;
                    }
                    ImGui::SameLine();
                    ImGui::Text("row 2 >=");
                    ImGui::SameLine();
                    if (ImGui::InputScalar("##3", ImGuiDataType_U8, &r1p, NULL, NULL, "%u")) {
                        if (r1p < 0)
                            r1p = 0;
                        else if (r1p > s1)
                            r1p = s1;
                    }
                }
                ImGui::SameLine();
                ImGui::Text("row 3 <=");
                ImGui::SameLine();
                if (ImGui::InputScalar("##4", ImGuiDataType_U8, &r3p, NULL, NULL, "%u")) {
                    if (r3p < 0)
                        r3p = 0;
                    else if (r3p > s1)
                        r3p = s1;
                }
                ImGui::SameLine();
                if (prob < 0.01) {
                    if (prob == 0.)
                        ImGui::Text(") = 0");
                    else ImGui::Text(") is about 1 in %u", static_cast<unsigned int>(round(1 / prob)));
                }
                else ImGui::Text(") = %.2f%%", 100 * prob);
                ImGui::Text("P(row 1 + row 2 >=");
                ImGui::SameLine();
                ImGui::PushItemWidth(25.0f);
                if (ImGui::InputScalar("##5", ImGuiDataType_U8, &r12p, NULL, NULL, "%u")) {
                    if (r12p < 0)
                        r12p = 0;
                    else if (r12p > 2 * s1)
                        r12p = 2 * s1;
                }
                ImGui::SameLine();
                ImGui::Text("row 3 <=");
                ImGui::SameLine();
                if (ImGui::InputScalar("##6", ImGuiDataType_U8, &r4p, NULL, NULL, "%u")) {
                    if (r4p < 0)
                        r4p = 0;
                    else if (r4p > s1)
                        r4p = s1;
                }
                ImGui::SameLine();
                if (prob2 < 0.01) {
                    if (prob2 == 0.)
                        ImGui::Text(") = 0");
                    else ImGui::Text(") is about 1 in %u", static_cast<unsigned int>(round(1 / prob2)));
                }
                else ImGui::Text(") = %.2f%%", 100 * prob2);
                if (p_ma && ImGui::Button("Calculate P")) {
                    if (psc)
                        update_probabilities(prob, prob2, p, smaxa, r1p, r2p, r3p, r12p, r4p, s1, r1s, r2s, r3s, row1, row2, row3, prob_t);
                    else update_probabilities(prob, prob2, p, smaxa, r1p, r2p, r3p, r12p, r4p, s1a, r1s, r2s, r3s, row1, row2, row3, prob_t);
                }
                ImGui::PopItemWidth();
            }
            else ImGui::Text("*can be slightly higher than actual value due to allowing it be chosen in a tie\n*probabilities need to be enabled to get actual value");
            ImGui::End();
        }
        else {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
            if (ImGui::Begin("Initiallizing Tables", NULL, window_flags2)) {
                if (progress == 0.0f) {
                    calcBaseTable(base_e, base_d);
                    progress = 0.01f;
                }
                else if (enable_p) {
                    initTables(start1, start2, d25, d35, d45, d55, d65, d75, e25, e35, e45, e55, e65, e75, p25, p35, p45, p55, p65, p75);
                    start2++;
                    if (start2 == 11) {
                        start2 = 0;
                        start1++;
                        if (start1 == 11) {
                            for (int i = 0; i < 6; i++) {
                                prob_t.push_back(std::vector<std::vector<std::vector<long double>>>());
                                dt.push_back(std::vector<std::vector<int>>());
                                exp.push_back(std::vector<std::vector<std::vector<long double>>>());
                            }
                            prob_t[0].swap(p25);
                            prob_t[1].swap(p35);
                            prob_t[2].swap(p45);
                            prob_t[3].swap(p55);
                            prob_t[4].swap(p65);
                            prob_t[5].swap(p75);
                            dt[0].swap(d25);
                            dt[1].swap(d35);
                            dt[2].swap(d45);
                            dt[3].swap(d55);
                            dt[4].swap(d65);
                            dt[5].swap(d75);
                            exp[0].swap(e25);
                            exp[1].swap(e35);
                            exp[2].swap(e45);
                            exp[3].swap(e55);
                            exp[4].swap(e65);
                            exp[5].swap(e75);
                            init = true;
                            start2 = 1;
                        }
                    }
                    progress += 0.99f / 121.0f;
                }
                else {
                    initTables2(start1, start2, d25, d35, d45, d55, d65, d75, e25, e35, e45, e55, e65, e75);
                    start2++;
                    if (start2 == 11) {
                        start2 = 0;
                        start1++;
                        if (start1 == 11) {
                            for (int i = 0; i < 6; i++) {
                                dt.push_back(std::vector<std::vector<int>>());
                                exp.push_back(std::vector<std::vector<std::vector<long double>>>());
                            }
                            dt[0].swap(d25);
                            dt[1].swap(d35);
                            dt[2].swap(d45);
                            dt[3].swap(d55);
                            dt[4].swap(d65);
                            dt[5].swap(d75);
                            exp[0].swap(e25);
                            exp[1].swap(e35);
                            exp[2].swap(e45);
                            exp[3].swap(e55);
                            exp[4].swap(e65);
                            exp[5].swap(e75);
                            init = true;
                        }
                    }
                    progress += 0.99f / 121.0f;
                }
                ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Text("initializing tables");
                if (start1 == 11) {
                    start1 = 0;
                    progress = 0.0f;
                }
            }
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
