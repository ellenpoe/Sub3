#pragma once

#include <boost/serialization/export.hpp>

#include "../Sub3.hpp"
#include "Message.hpp"
#include "../simulation/VesselState.hpp"
#include "../simulation/Ocean.hpp"

//Template to allow any vessel to have a spawn message
template <class VesselClass> class SpawnMessage : public Message
{
    //Serialization boilerplate
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Message>(*this);
        ar & initialState;
    }

public:
    SpawnMessage()
    {
    }

    SpawnMessage(VesselID vesselID, VesselState initialState) :
        initialState(initialState)
    {
        this->vesselID = vesselID;
    }

    void execute()
    {
        //Don't run the packet if it wasn't created properly.
        if (this->vesselID.getPlayer() == -1)
        {
            subDebug << "SpawnMessage: Player #-1 undefined" << std::endl;
            return;
        }
        std::shared_ptr<VesselClass> vessel = std::make_shared<VesselClass>();
        Ocean::getOcean()->localSpawnVessel(vesselID, vessel);
    }

    VesselState initialState;

private:

};