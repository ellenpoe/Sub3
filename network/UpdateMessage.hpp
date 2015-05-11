#pragma once

#include "Message.hpp"
#include "../simulation/VesselState.hpp"

class UpdateMessage : public Message
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Message>(*this);
        ar & newState;
    }

public:
    UpdateMessage();
    UpdateMessage(VesselID vesselID, VesselState newState);

    void execute();

    VesselState newState;

private:

};