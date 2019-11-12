import Cocoa

class ViewController: NSViewController {
    
    var guiLiteView: GuiLiteView? = nil

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        Thread.detachNewThreadSelector(#selector(ViewController.runNative), toTarget: self, with: nil)
        sleep(2)
        Timer.scheduledTimer(withTimeInterval: 0.04, repeats: true, block: {_ in self.updateNativeView()})
        
        self.guiLiteView = GuiLiteView(frame: CGRect(x: 0, y: 0, width: 1024, height: 768))
        self.guiLiteView?.setSize(width: 1024, height: 768)
        view.addSubview(self.guiLiteView!)
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
    
    @objc func runNative()
    {
        _startHostMonitor(1024, 768, 4)
    }
    
    func updateNativeView(){
        self.guiLiteView?.needsDisplay = true
    }
}
