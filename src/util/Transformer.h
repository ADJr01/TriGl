//
// Created by STHEP on 9/20/2025.
//

#ifndef TRIGL_TRANSFORMER_H
#define TRIGL_TRANSFORMER_H
class Transformer {
private:
    float moveOffset=0.3,moveSpeedPerFrame=0.003,MaxMoveRight=0.5,MaxMoveLeft=-0.5,rotationSpeed=0.3f;
    bool isMovingRight=true;
    //rotation
    float rotation = 0.0f;
public:
    Transformer()=default;
    void movementOffset() {
        if (isMovingRight) {
            moveOffset += moveSpeedPerFrame;
            (moveOffset >= MaxMoveRight) ?( isMovingRight = false):isMovingRight;
        } else {
            moveOffset -= moveSpeedPerFrame;
            if (moveOffset <= MaxMoveLeft) {
                moveOffset = MaxMoveLeft; // clamp
                isMovingRight = true;
            }
        }
    }
    float& getMoveOffset() {
        return moveOffset;
    }
    float& getNextRotation() {
        if (isMovingRight) {
            rotation -= rotationSpeed;
        }else {
            rotation += rotationSpeed;
        }
        return rotation;
    }
};

#endif //TRIGL_TRANSFORMER_H