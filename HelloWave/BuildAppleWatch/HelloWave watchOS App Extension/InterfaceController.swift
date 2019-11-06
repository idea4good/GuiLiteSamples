import WatchKit
import Foundation
import SpriteKit


class InterfaceController: WKInterfaceController {

    fileprivate let viewWidth = 240
    fileprivate var viewHeight = 190//320//280
    fileprivate var colorBytes = 4
    
    @IBOutlet var skInterface: WKInterfaceSKScene!
    fileprivate var guiLiteImage : GuiLiteImage?
    fileprivate var scene : GameScene?
    fileprivate var guiLiteNode : SKSpriteNode?
    
    override func awake(withContext context: Any?) {
        super.awake(withContext: context)
        
        scene = GameScene.newGameScene()
        
        // Present the scene
        self.skInterface.presentScene(scene)
        
        // Use a preferredFramesPerSecond that will maintain consistent frame rate
        self.skInterface.preferredFramesPerSecond = 30
        
        guiLiteNode = SKSpriteNode()
        guiLiteNode?.size = CGSize(width: 1000, height: 1000)
        guiLiteImage = GuiLiteImage(width: viewWidth, height: viewHeight, colorBytes: colorBytes)
        Thread.detachNewThreadSelector(#selector(starUI), toTarget: self, with: nil)
        sleep(2)// Wait for GuiLite App ready
        Timer.scheduledTimer(withTimeInterval: 0.04, repeats: true, block: {_ in self.updateNativeView()})
    }
    
    override func willActivate() {
        // This method is called when watch view controller is about to be visible to user
        super.willActivate()
    }
    
    override func didDeactivate() {
        // This method is called when watch view controller is no longer visible
        super.didDeactivate()
    }

    func updateNativeView() {
        let cgGuiLiteImage = guiLiteImage?.getUiImage()
        if(cgGuiLiteImage == nil){
            return
        }
        guiLiteNode!.removeFromParent()
        guiLiteNode!.texture = SKTexture(cgImage: cgGuiLiteImage!)
        scene?.addChild(guiLiteNode!)
    }
    
    @objc func starUI(){
        startHelloWave(calloc(viewWidth * viewHeight, colorBytes), Int32(viewWidth), Int32(viewHeight), Int32(colorBytes), nil);
    }
}
