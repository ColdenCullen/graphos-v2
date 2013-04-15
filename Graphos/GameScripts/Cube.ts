/// <reference path="Graphos.ts" />

// Class
class Cube extends GameObject
{
    // Constructor
    constructor()
    {
        super();
    }

    Update( deltaTime: number ): void
    {
        //if( Input.IsKeyDown( Keys["w"] ) )
        //    console.log( "W KEY IS DOWWWWN" );

        if( Input.IsKeyDown( Keys.space ) )
            console.log( this.transform.position.x );
    }
}