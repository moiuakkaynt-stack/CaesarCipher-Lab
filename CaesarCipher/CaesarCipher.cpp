#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>

std::wstring caesarTransform(const std::wstring& text, int uaShift, int latinShift)
{
    const std::wstring uaUpper = L"АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
    const std::wstring uaLower = L"абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
    const std::wstring laUpper = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::wstring laLower = L"abcdefghijklmnopqrstuvwxyz";
    uaShift %= static_cast<int>(uaUpper.size());
    latinShift %= static_cast<int>(laUpper.size());
    std::wstring result;
    for (wchar_t ch : text)
    {
        std::size_t pos = uaUpper.find(ch);
        if (pos != std::wstring::npos)
            result += uaUpper[(pos + uaShift + uaUpper.size()) % uaUpper.size()];
        else
        {
            pos = uaLower.find(ch);
            if (pos != std::wstring::npos)
                result += uaLower[(pos + uaShift + uaLower.size()) % uaLower.size()];
            else
            {
                pos = laUpper.find(ch);
                if (pos != std::wstring::npos) result += laUpper[(pos + latinShift + laUpper.size()) % laUpper.size()];
                else { pos = laLower.find(ch); if (pos != std::wstring::npos) result += laLower[(pos + latinShift + laLower.size()) % laLower.size()]; else result += ch; }
            }
        }
    }
    return result;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::wcout << L"Введіть український текст: ";
    std::wstring text;
    std::getline(std::wcin, text);
    if (text.empty())
    {
        std::wcout << L"Помилка: текст не може бути порожнім.\n";
        return 1;
    }

    std::wcout << L"Введіть зсув для українського алфавіту: ";
    int shift = 0;
    if (!(std::wcin >> shift))
    {
        std::wcout << L"Помилка: зсув має бути цілим числом.\n";
        return 1;
    }

    if (shift == 0 || shift % 33 == 0)
    {
        std::wcout << L"Помилка: зсув, кратний довжині українського алфавіту (33), не змінює текст.\n";
        return 1;
    }

    std::wcout << L"Введіть зсув для латинського алфавіту: ";
    int latinShift = 0;
    if (!(std::wcin >> latinShift)) { std::wcout << L"Помилка: латинський зсув має бути цілим числом.\n"; return 1; }
    if (latinShift == 0 || latinShift % 26 == 0) { std::wcout << L"Помилка: латинський зсув, кратний 26, не змінює текст.\n"; return 1; }
    std::wcout << L"Результат: " << caesarTransform(text, shift, latinShift) << L"\n";
    std::wcout << L"Символи поза алфавітом збережено.\n";
    return 0;
}
