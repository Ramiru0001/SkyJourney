#pragma once
#include <GLLibrary.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <cmath>
//#include <GL/glut>
#include <algorithm>
#include "Management/Task.h"
#include "Management/Progress.h"
#include "Public/PublicFile.h"
#include "Game/Field.h"
#include "Game/Object.h"
#include "Game/SkyBox.h"
#include "Character/Player.h"
#include "Character/Whale.h"
#include "Camera/Camera.h"
#include "Title/Title.h"
#include "System/UI.h"
#include "System/Effect.h"
#define GRAVITY (0.01f)
#define JUMP (0.2f)
#define FLY (0.4f)
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DEFAULT_POS CVector3D(0,5,0)