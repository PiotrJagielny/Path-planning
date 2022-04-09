#include "Headers.h"
#include "Constants.h"


const unsigned Constants::windowWidth = 1000;
const unsigned Constants::windowHeigth = 1000;

const float Constants::gridSizeFloat = 25.0f;
const unsigned Constants::gridSizeUnsigned = static_cast<unsigned>(Constants::gridSizeFloat);

const int Constants::mapSizeX = Constants::windowWidth / Constants::gridSizeFloat;
const int Constants::mapSizeY = Constants::windowHeigth / Constants::gridSizeFloat;

bool Constants::singleQuitClickDetection = false;
bool Constants::insertStartPosition = false;
bool Constants::insertEndPosition = false;
bool Constants::isStaticModeSeleceted = false;
bool Constants::isDynamicModeSelected = false;