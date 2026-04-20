#include <string.h>

#include "nodedata.h"

int CompareKeys(NodeData left, NodeData right) {
	return strcmp(left.key, right.key);
}