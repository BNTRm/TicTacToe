#pragma once

#include "MyLib.h"

using namespace MyLib;

namespace WinCheck {

	bool checkRowAndCol(Field& f, size_t index);
	bool checkNonCentralDiag(Field& f, size_t index);
	bool check(Field& f);
}