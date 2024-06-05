#pragma once
#include <gint/kmalloc.h>
#include <string.h>

#ifndef RMX_BOX
#define RMX_BOX

#define TRUE 1
#define FALSE 0

#define BOX_MAX_WIDTH 128
#define BOX_MAX_HEIGHT 64
#define BOX_MAX_X BOX_MAX_WIDTH -1
#define BOX_MAX_Y BOX_MAX_HEIGHT -1
#define BOXES_MAX_AMOUNT 16

typedef unsigned char bool;

typedef signed char bHandle;
typedef signed char box_t;
typedef signed char int8_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef signed char boxErr_t;

boxErr_t lastBoxErr;
#define boxErrCheck(boxHandle, retVal) \
    if (isBoxHandledList[boxHandle] == 0)\
    {\
    lastBoxErr = BOX_ERR_BOX_DOESNT_EXIT;\
    return retVal;\
    }

#define valueCheck(value, minVal, maxVal) \
    if (value < minVal)\
    {\
	value = minVal;\
    }\
    else if (value > maxVal)\
    {\
	value = maxVal;\
    }

struct Box;
struct tblr;

struct Box* boxes[BOXES_MAX_AMOUNT];
bool isBoxHandledList[BOXES_MAX_AMOUNT];

struct Box
{
    box_t type;
    int8_t x, y;
    int8_t width, height;
    union
    {
	int32_t margin;
        struct {int8_t marginTop, marginBot, marginLeft, marginRight; };
    }
    union
    {
	int32_t border;
        struct {int8_t borderTop, borderBot, borderLeft, borderRight; };
    }
    union
    {
	int32_t padding;
        struct {int8_t paddingTop, paddingBot, paddingLeft, paddingRight; };
    }
    char* title;
    void* buffer;
    int32_t bufferSize;
    bool hidden;
};

struct tblr
{
    int8_t top, bot, left, right;
};

enum
{
    // Box types
    BOX_TYPE_NULL = 0,
    BOX_TYPE_TEXT = 1,
    BOX_TYPE_INPUT = 2,

    // Negations
    BOX_NO_BORDER = -1,
    BOX_NO_MARGIN = -1,

    // Errors
    BOX_NO_ERROR = 0,
    BOX_ERR_BOX_DOESNT_EXIT = -1,
    BOX_ERR_MAXIMUM_REACHED = -1,
    BOX_ERR_BAD_VALUE = -2,

};

// Function prototypes

// Create / Delete
bHandle createBox(box_t type, int8_t x, int8_t y, int8_t width, int8_t height, int8_t marginTop, int8_t marginBot, int8_t marginLeft, int8_t marginRight, int8_t borderTop, int8_t borderBot, int8_t borderLeft, int8_t borderRight, int8_t paddingTop, int8_t paddingBot, int8_t paddingLeft, int8_t paddingRight, const char* title, void* buffer, int32_t bufferSize)
void deleteBox(bHandle boxHandle)
bHandle createBoxHandle(void);
boxErr_t deleteBoxHandle(bHandle boxHandle);

// Setters

boxErr_t boxSetType(bHandle boxHandle, box_t type);

boxErr_t boxSetX(bHandle boxHandle, int8_t x);
boxErr_t boxSetY(bHandle boxHandle, int8_t y);
boxErr_t boxSetWidth(bHandle boxHandle, int8_t width);
boxErr_t boxSetHeight(bHandle boxHandle, int8_t height);

boxErr_t boxSetMargin(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right);
boxErr_t boxSetBorder(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right);
boxErr_t boxSetPadding(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right);

boxErr_t boxSetTitle(bHandle boxHandle, const char* title);
boxErr_t boxSetBuffer(bHandle boxHandle, void* type, int32_t bufferSize);


// Getters

box_t boxGetType(bHandle boxHandle);

int8_t boxGetX(bHandle boxHandle);
int8_t boxGetY(bHandle boxHandle);
int8_t boxGetWidth(bHandle boxHandle);
int8_t boxGetHeight(bHandle boxHandle);

int32_t boxGetMargin(bHandle boxHandle);
int32_t boxGetBorder(bHandle boxHandle);
int32_t boxGetPadding(bHandle boxHandle);

const char* boxGetTitle(bHandle boxHandle);
boxErr_t boxGetBuffer(bHandle boxHandle, void* type, int32_t bufferSize);

// Show / Hide boxes
boxErr_t showBox(bHandle boxHandle);
boxErr_t showAllBoxes(void);

boxErr_t hideBox(bHandle boxHandle);
boxErr_t hideAllBoxes(void);

boxErr_t drawBox(bHandle boxHandle);
boxErr_t drawAllBoxes(void);


bHandle createBox(box_t type, int8_t x, int8_t y, int8_t width, int8_t height, int8_t marginTop, int8_t marginBot, int8_t marginLeft, int8_t marginRight, int8_t borderTop, int8_t borderBot, int8_t borderLeft, int8_t borderRight, int8_t paddingTop, int8_t paddingBot, int8_t paddingLeft, int8_t paddingRight, const char* title, void* buffer, int32_t bufferSize, bool hidden)
{
    // Create handle for the box
    bHandle handle = createBoxHandle();
    if (handle < 0) return -1;
    boxes[handle] = kmalloc(sizeof(Box), NULL);
    boxSetType(handle, type);
    boxSetX(handle, x);
    boxSetY(handle, y);
    boxSetWidth(handle, width);
    boxSetHeight(handle, height);
    boxSetMargin(handle, marginTop, marginBot, marginLeft, marginRight);
    boxSetBorder(handle, borderTop, borderBot, borderLeft, borderRight);
    boxSetPadding(handle, paddingTop, paddingBot, paddingLeft, paddingRight);
    boxSetTitle(handle, title);
    boxSetBuffer(handle, buffer, bufferSize);
    showBox(handle);
    return handle;
}

void deleteBox(bHandle boxHandle)
{
    deleteBoxHandle(boxHandle);
    kfree(boxes[boxHandle]);
}

bHandle createBoxHandle(void)
{
    for (int i = 0; i < BOXES_MAX_AMOUNT; i++)
        if (isBoxHandledList[i] == 0)
	{
	    isBoxHandledList[i] = 1;
            return i;
	}
    return BOX_ERR_MAXIMUM_REACHED;    
}

boxErr_t deleteBoxHandle(bHandle boxHandle)
{
    if ( isBoxHandledList[bHandle] == 0) return BOX_ERR_BOX_DOESNT_EXIT;
    isBoxHandledList[boxHandle] = 0;
    return BOX_NO_ERROR;
}

// Setters

boxErr_t boxSetType(bHandle boxHandle, box_t type)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(type, 0, 2)
    boxes[boxHandle]->type = type; 
}

boxErr_t boxSetX(bHandle boxHandle, int8_t x)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(x, 0, BOX_MAX_X)
    boxes[boxHandle]->x = x; 
}
boxErr_t boxSetY(bHandle boxHandle, int8_t y)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(y, 0, BOX_MAX_Y)
    boxes[boxHandle]->y = y; 
}
boxErr_t boxSetWidth(bHandle boxHandle, int8_t width)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(width, 0, BOX_MAX_WIDTH)
    boxes[boxHandle]->width = width; 
}
boxErr_t boxSetHeight(bHandle boxHandle, int8_t height)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(height, 0, BOX_MAX_HEIGHT)
    boxes[boxHandle]->height = height; 
}

boxErr_t boxSetMargin(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(top, 0, BOX_MAX_HEIGHT)
    valueCheck(bot, 0, BOX_MAX_HEIGHT)
    valueCheck(left, 0, BOX_MAX_WIDTH)
    valueCheck(right, 0, BOX_MAX_WIDTH)
    boxes[boxHandle]-> = type; 
}
boxErr_t boxSetBorder(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(top, 0, BOX_MAX_HEIGHT)
    valueCheck(bot, 0, BOX_MAX_HEIGHT)
    valueCheck(left, 0, BOX_MAX_WIDTH)
    valueCheck(right, 0, BOX_MAX_WIDTH)
    boxes[boxHandle]->type = type; 
}
boxErr_t boxSetPadding(bHandle boxHandle, int8_t top, int8_t bot, int8_t left, int8_t right)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(top, 0, BOX_MAX_HEIGHT)
    valueCheck(bot, 0, BOX_MAX_HEIGHT)
    valueCheck(left, 0, BOX_MAX_WIDTH)
    valueCheck(right, 0, BOX_MAX_WIDTH)
    boxes[boxHandle]->type = type; 
}

boxErr_t boxSetTitle(bHandle boxHandle, const char* title)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(type, 0, 2)
    boxes[boxHandle]->type = type; 
}
boxErr_t boxSetBuffer(bHandle boxHandle, void* type, int32_t bufferSize)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    valueCheck(type, 0, 2)
    boxes[boxHandle]->type = type; 
}


// Getters

box_t boxGetType(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->type;
}

int8_t boxGetX(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->x;
}
int8_t boxGetY(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->y;
}
int8_t boxGetWidth(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->width;
}
int8_t boxGetHeight(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->height;
}

int32_t boxGetMargin(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->margin;
}
int32_t boxGetBorder(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->border;
}
int32_t boxGetPadding(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    return boxes[boxHandle]->padding;
}

const char* boxGetTitle(bHandle boxHandle)
{
    boxErrCheck(boxHandle, "")
    return (const char*) *(boxes[boxHandle]->title);
}
void* boxGetBuffer(bHandle boxHandle)
{
    boxErrCheck(boxHandle, NULL)
    return boxes[boxHandle]->buffer;
}
int32_t boxGetBufferSize(bHandle boxHandle)
{
    boxErrCheck(boxHandle, -1)
    return boxes[boxHandle]->bufferSize;
}

// Show / Hide boxes
boxErr_t showBox(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    if (isBoxHandledList[boxHandle] == 0)
    {
	lastBoxErr = BOX_ERR_BOX_DOESNT_EXIT;
	return BOX_ERR_BOX_DOESNT_EXIT;
    }
    boxes[boxHandle]->hidden = FALSE;
    return BOX_NO_ERROR;
}
boxErr_t showAllBoxes(void)
{
    lastBoxErr = BOX_NO_ERROR;
    int8_t boxesShown = 0;
    for (int i = 0; i < BOXES_MAX_AMOUNT; i++)
	if (isBoxHandledList[i] == 1)
	{
		boxes[i].hidden == FALSE;
		boxesShown++;
	}
    if (lastBoxErr == BOX_NO_ERROR) return boxesShown;
    return boxesShown * -1;
}

boxErr_t hideBox(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    boxes[boxHandle]->hidden = TRUE;
    return BOX_NO_ERROR;
}
int8_t hideAllBoxes(void)
{
    lastBoxErr = BOX_NO_ERROR;
    int8_t boxesHidden = 0;
    for (int i = 0; i < BOXES_MAX_AMOUNT; i++)
	if (isBoxHandledList[i] == 1)
	{
		boxes[i].hidden == TRUE;
		boxesHidden++;
	}
    if (lastBoxErr == BOX_NO_ERROR) return boxesHidden;
    return boxesHidden * -1;
}

boxErr_t drawBox(bHandle boxHandle)
{
    boxErrCheck(boxHandle, BOX_ERR_BOX_DOESNT_EXIT)
    if (boxes[boxHandle]->margin != 0)
        drect((int)boxes[boxHandle]->x, (int)boxes[boxHandle]->y, (int)boxes[boxHandle]->x + (int)boxes[boxHandle]->width - 1, (int)boxes[boxHandle]->y + (int)boxes[boxHandle]->height - 1, C_BLACK);
    if (boxes[boxHandle]->border != 0)
        drect((int)boxes[boxHandle]->x + (int)boxes[boxHandle]->marginLeft, (int)boxes[boxHandle]->y + (int)boxes[boxHandle]->marginTop, (int)boxes[boxHandle]->x + (int)boxes[boxHandle]->width - 1 - (int)boxes[boxHandle]->marginRight, (int)boxes[boxHandle]->y + (int)boxes[boxHandle]->height - 1 - (int)boxes[boxHandle]->marginBot, C_BLACK);
    if (boxes[boxHandle]->margin == 0 || boxes[boxHandle]->border != 0)
        drect((int)boxes[boxHandle]->x + (int)boxes[boxHandle]->marginLeft + (int)boxes[boxHandle]->borderLeft, (int)boxes[boxHandle]->y + (int)boxes[boxHandle]->marginTop + (int)boxes[boxHandle]->borderTop, (int)boxes[boxHandle]->x + (int)boxes[boxHandle]->width - 1 - (int)boxes[boxHandle]->marginRight - (int)boxes[boxHandle]->borderRight, (int)boxes[boxHandle]->y + (int)boxes[boxHandle]->height - 1 - (int)boxes[boxHandle]->marginBot - (int)boxes[boxHandle]->borderBot, C_BLACK);
    return BOX_NO_ERROR;
}
int8_t drawAllBoxes(void)
{
    lastBoxErr = BOX_NO_ERROR;
    int8_t boxesDrawn = 0;
    for (int i = 0; i < BOXES_MAX_AMOUNT; i++)
	if (boxes[i].hidden == FALSE)
	{
            drawBox(isBoxHandledList[i]);
	    boxesDrawn++;
	}
    if (lastBoxErr == BOX_NO_ERROR) return boxesDrawn;
    return boxesDrawn * -1;
}

#endif
