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
    public $image = NULL;  
    public $output = NULL;  
    public $_prefix = 'IMG';  
    private $_width = NULL;  
    private $_height = NULL;  
    private $_tmp = NULL;  
   
    public static function factory($image, $output)  
    {  
        return new Instagraph($image, $output);  
    }  
   
    public function __construct($image, $output)  
    {  
        if(file_exists($image)) {
            $this->image = $image;
            $this->output = $output; 
        } else {  
            throw new Exception('File not found. Aborting.');  
        }  
    }  
   
    public function tempfile()  
    {  
        # copy original file and assign temporary name  
        $this->_tmp = $this->_prefix.rand();  
        copy($this->_image, $this->_tmp);  
    }  
   
    public function output()  
    {  
        # rename working temporary file to output filename  
        rename($this->_tmp, $this->_output);  
    }  
   
    public function execute($command)  
    {  
        # remove newlines and convert single quotes to double to prevent errors  
        $command = str_replace(array("\n", "'"), array('', '"'), $command);  
        $command = escapeshellcmd($command);  
        # execute convert program  
        exec($command);  
    }  
   
    /** ACTIONS */  
   
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
   
    public function border($input, $color = 'black', $width = 20)  
    {  
        $this->execute("convert $input -bordercolor $color -border {$width}x{$width} $input");  
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