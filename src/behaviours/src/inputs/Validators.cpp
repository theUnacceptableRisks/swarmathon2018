#include "InputLocation.h"
#include "InputSonarArray.h"
#include "InputTags.h"

VALIDATOR iolocation_validator = { IOTYPE_LOC, sizeof( InputLocation ), SUM_LOC };
VALIDATOR iosonar_validator = { IOTYPE_SONAR, sizeof( InputSonarArray ), SUM_SON };
VALIDATOR iotags_validator = { IOTYPE_TAGS, sizeof( InputTags ), SUM_TAG };

