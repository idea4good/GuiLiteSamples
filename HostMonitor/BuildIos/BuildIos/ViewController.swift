//
//  ViewController.swift
//  BuildIos
//
//  Created by Zorro Young on 2/1/18.
//  Copyright © 2018 Zorro Young. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var imgView: UIImageView!
    var isMouseDown = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        Thread.detachNewThreadSelector(#selector(ViewController.runNative), toTarget: self, with: nil)
        Timer.scheduledTimer(withTimeInterval: 0.04, repeats: true, block: {_ in self.updateNativeView()})
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let touch = touches.first{
            let pos = touch.location(in: self.imgView)
        
            mouse_down(Int32(pos.x), Int32(pos.y))
            self.isMouseDown = true
        }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let touch = touches.first{
            let pos = touch.location(in: self.imgView)
            
            mouse_up(Int32(pos.x), Int32(pos.y))
            self.isMouseDown = false
        }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        if self.isMouseDown == false{
            return
        }
        
        if let touch = touches.first{
            let pos = touch.location(in: self.imgView)
            
            mouse_down(Int32(pos.x), Int32(pos.y))
        }
    }

    func buildImage(imgWidth: Int, imgHeight: Int) -> UIImage?{
        let pixData = getPixels(imgWidth: imgWidth, imgHeight: imgHeight)
        if(pixData == nil){
            return nil
        }
        let providerRef = CGDataProvider(data: pixData!)
        let cgimg = CGImage.init(width: imgWidth, height: imgHeight, bitsPerComponent: 8, bitsPerPixel: 32, bytesPerRow: imgWidth*4, space: CGColorSpaceCreateDeviceRGB(), bitmapInfo: CGBitmapInfo.byteOrder32Big, provider: providerRef!, decode: nil, shouldInterpolate: true, intent: .defaultIntent)
        
        return UIImage(cgImage: cgimg!)
    }
    
    func getPixels(imgWidth: Int, imgHeight: Int)->CFData?{
        let dataLength = imgWidth * imgHeight * 4
        let buffer = malloc(dataLength)
        
        let rawData = get_frame_buffer(0, nil, nil)
        if rawData == nil{
            return nil
        }
        
        for index in 0..<imgWidth*imgHeight {
            let rgb16 = rawData?.load(fromByteOffset: index * 2, as: UInt16.self)
            let rgb32 = UInt32(rgb16!)
            let color = ((rgb32 << 19) & 0xFF0000) | (((rgb32) << 5) & 0xFF00) | ((rgb32 >> 8) & 0xFF)
            buffer?.storeBytes(of: color, toByteOffset: index * 4, as: UInt32.self)
        }
        
        let rawPointer = UnsafeRawPointer(buffer)
        free(buffer)
        
        let pixData: UnsafePointer = rawPointer!.assumingMemoryBound(to: UInt8.self)
        return CFDataCreate(nil, pixData, dataLength)
    }
    
    func updateNativeView(){
        if(self.imgView == nil){
            return
        }
        self.imgView.image = buildImage(imgWidth: 1024, imgHeight: 768)
        self.imgView.setNeedsDisplay()
    }
    
    func runNative(){
        run_host_monitor()
    }
}
