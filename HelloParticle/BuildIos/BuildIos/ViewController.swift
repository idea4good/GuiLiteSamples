import UIKit

class ViewController: UIViewController {
    let guiWidth = 240
    let guiHeight = 320
    let guiColorBytes = 4
    var isMouseDown = false
    let guiLiteImage: GuiLiteImage
    @IBOutlet weak var imgView: UIImageView!
    
    required init(coder aDecoder: NSCoder) {
        guiLiteImage = GuiLiteImage(width: guiWidth, height: guiHeight, colorBytes: guiColorBytes)
        super.init(coder: aDecoder)!
    }
    
    @objc func starUI(){
        startHelloParticle(calloc(guiWidth * guiHeight, guiColorBytes), Int32(guiWidth), Int32(guiHeight), Int32(guiColorBytes), nil);
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let pos = touchPosToNative(touches: touches)
        //sendTouch2Hello(pos.0, pos.1, true)
        self.isMouseDown = true
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        let pos = touchPosToNative(touches: touches)
        //sendTouch2Hello(pos.0, pos.1, false)
        self.isMouseDown = false
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        if self.isMouseDown == false{
            return
        }
        let pos = touchPosToNative(touches: touches)
        //sendTouch2Hello(pos.0, pos.1, true)
    }

    func touchPosToNative(touches: Set<UITouch>)->(Int32, Int32){
        if let touch = touches.first{
            let pos = touch.location(in: self.imgView)
            return (Int32(CGFloat(self.guiWidth) * pos.x / self.imgView.frame.size.width), Int32(CGFloat(self.guiHeight) * pos.y / self.imgView.frame.size.height))
        }
        return (0, 0)
    }

    func updateNativeView() {
        let uiImage = guiLiteImage.getUiImage()
        if(uiImage == nil){
            return
        }
        self.imgView.image = uiImage
        self.imgView.setNeedsDisplay()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        Thread.detachNewThreadSelector(#selector(starUI), toTarget: self, with: nil)
        sleep(2)// Wait for GuiLite App ready
        Timer.scheduledTimer(withTimeInterval: 0.04, repeats: true, block: {_ in self.updateNativeView()})
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
