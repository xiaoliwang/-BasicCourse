<?php
/*$imgick = new Imagick('1.jpg');
// 修改尺寸 长，宽，filter，模糊 
$imgick->resizeImage(640, 480, Imagick::FILTER_LANCZOS, 0.8);
$imgick->writeImage('2.jpg');
$imgick->clear();
$imgick->destroy();*/

/**
 * modulate: 调整亮度，饱和度和色相
 * constrast: 提高或降低图片对比度
 * size: 调整图像高度或宽度
 * fill: 当填充原始图形时着色
 * draw: 使用原始图形来标注图像
 * compose: 设置图像合成操作
 * channel: 应用选项来选择图像通道
 * level: 调整图像对比度水平
 * auto-gamma: 自动调整图像伽马水平
 * gamma: 伽马校正的水平 
 *
 */

class Instagraph  
{    
    public $filename;  
    public $new_filename;
    private $_image;  
    private $_width;  
    private $_height;  
   
    public static function factory($filename, $new_filename)  
    {  
        return new Instagraph($filename, $new_filename);  
    }  
   
    public function __construct($filename, $new_filename)  
    {  
        if(file_exists($filename)) {
            $image = new Imagick($filename);
            $size = $image->getImageGeometry();
            $this->_width = $size['width'];
            $this->_height = $size['height'];
            $this->_image = $image;
            $this->filename = $filename;         
            $this->new_filename = $new_filename; 
        } else {  
            throw new Exception('File not found. Aborting.');  
        }  
    }

    // 添加边框
    public function addBorder($color = 'black', $width = 20, $height = 0)
    {
        $height = $height ?: $width;
        $this->_image->borderImage($color, $width, $height);
    }

    // 调整图片亮度，饱和度(色彩是否丰富)，色调(冷色还是暖色)
    public function modulate($brightness, $saturation, $hue)
    {
        $this->_image->modulateImage($brightness, $saturation, $hue);
    }

    // 添加填充色彩
    public function colorize($color, $opacity)
    {
        $this->_image->colorizeImage($color, $opacity, true);
    }

    // gamma矫正
    public function gamma($gamma)
    {
        $this->_image->gammaImage($gamma, Imagick::CHANNEL_ALL);
    }

    public function output()  
    {  
        $this->_image->writeImage($this->new_filename); 
    }   

    public function clear()
    {
        $this->_image->clear();
        $this->_image->destroy();
    }
   
    /** 待研究 */  
    public function colortone($input, $color, $level, $type = 0)  
    {  
        $args[0] = $level;  
        $args[1] = 100 - $level;  
        $negate = $type == 0? '-negate': '';  
   
        $this->execute("convert  
        {$input}  
        ( -clone 0 -fill '$color' -colorize 100% )  
        ( -clone 0 -colorspace gray $negate )  
        -compose blend -define compose:args=$args[0],$args[1] -composite  
        {$input}");  
    }  
   
    public function frame($input, $frame)  
    {  
        $this->execute("convert $input ( '$frame' -resize {$this->_width}x{$this->_height}! -unsharp 1.5×1.0+1.5+0.02 ) -flatten $input");  
    }  
   
    public function vignette($input, $color_1 = 'none', $color_2 = 'black', $crop_factor = 1.5)  
    {  
        $crop_x = floor($this->_width * $crop_factor);  
        $crop_y = floor($this->_height * $crop_factor);  
   
        $this->execute("convert  
        ( {$input} )  
        ( -size {$crop_x}x{$crop_y}  
        radial-gradient:$color_1-$color_2  
        -gravity center -crop {$this->_width}x{$this->_height}+0+0 +repage )  
        -compose multiply -flatten  
        {$input}");  
    }
}
// convert  -fill '#222b6d' -colorize 20 -gamma 0.5 -contrast -contrast
$image = Instagraph::factory('./1.jpg', './2.jpg');
$image->modulate(120, 10, 100);
$image->colorize('#222b6d', 1);
$image->gamma(0.5);
$image->addBorder('white', 50);
$image->output();
$image->clear();