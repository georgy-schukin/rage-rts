#include "compfragment.h"

namespace fprts {

void CompFragment::Pack(Message &msg) { // pack itself to buffer	
	Fragment::Pack(msg);
}

void CompFragment::Unpack(Message &msg) { // unpack itself from buffer
	Fragment::Unpack(msg);
}

}