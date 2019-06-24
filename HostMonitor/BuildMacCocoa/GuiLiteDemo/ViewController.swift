import Cocoa

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        Thread.detachNewThreadSelector(#selector(ViewController.runNative), toTarget: self, with: nil)
        Timer.scheduledTimer(withTimeInterval: 0.04, repeats: true, block: {_ in self.updateNativeView()})
        
        let frame = CGRect(x: 0, y: 0, width: 1024, height: 768)
        self.nativeView = NativeView(frame: frame)
        self.nativeView?.setNativeUiSize(width: 1024, height: 768)
        view.addSubview(self.nativeView!)
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
    
    @objc func runNative()
    {
        run_host_monitor();
    }
    
    func updateNativeView(){
        if(self.nativeView == nil){
            return
        }
        self.nativeView?.needsDisplay = true
    }
    
    var nativeView: NativeView? = nil
}
