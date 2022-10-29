/**
 * @file KillFoeVisitor.cpp
 * @author brend
 */

#include "KillFoeVisitor.h"
#include "Foe.h"

/**
 * Visit a foe and remove it from the game if it is in a down state.
 * @param foe The foe we are visiting
 */
void KillFoeVisitor::VisitFoe(Foe* foe)
{
    auto body = foe->GetBody();
    auto position = foe->GetBodyPosition();
    auto down = foe->GetDown();
    // If the position is below the down position, remove the foe from the world and set it to dead.
    if (position.y < down)
    {
        foe->GetWorld()->DestroyBody(body);
        foe->SetAliveState(false);
    }
}
