var __extends = this.__extends || function (d, b) {
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
/// <reference path="Graphos.ts" />
// Class
var Cube = (function (_super) {
    __extends(Cube, _super);
    // Constructor
    function Cube() {
        _super.call(this);
    }
    Cube.prototype.Update = function (deltaTime) {
        //if( Input.IsKeyDown( Keys["w"] ) )
        //    console.log( "W KEY IS DOWWWWN" );
        if(Input.IsKeyDown(Keys.space)) {
            console.log(this.transform.position.x);
        }
    };
    return Cube;
})(GameObject);
//@ sourceMappingURL=Cube.js.map
