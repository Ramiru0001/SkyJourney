#pragma once
#include <GLLibrary.h>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <iostream>
#include "TaskSystem/Task.h"
#include "Public/PublicFile.h"
#include "Game/Field.h"
#include "Game/Object.h"
#define GRAVITY (0.01f)
#define JUMP (0.4f)
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define DEFAULT_POS CVector3D(0,5,0)