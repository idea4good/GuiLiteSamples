import WatchKit
import Foundation


class InterfaceController: WKInterfaceController {

    fileprivate let viewWidth = 240
    fileprivate var viewHeight = 320
    fileprivate var colorBytes = 4
    
    @IBOutlet weak var image: WKInterfaceImage!
    fileprivate var guiLiteImage : GuiLiteImage?
    
    override func awake(withContext context: Any?) {
        super.awake(withContext: context)
        
        // Configure interface objects here.
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
        image.setImage(UIImage(cgImage: cgGuiLiteImage!))
    }

    @objc func starUI(){
        startHello3D(calloc(viewWidth * viewHeight, colorBytes), Int32(viewWidth), Int32(viewHeight), Int32(colorBytes), nil);
    }
}
