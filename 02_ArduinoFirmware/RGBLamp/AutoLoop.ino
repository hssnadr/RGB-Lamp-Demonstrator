// Auto loop: play random animation before first serial input
bool _isAnimRunning = false;
long _timerAutoLoop = 0;
int _targRed = 0;
int _targGreen = 0;
int _targBlue = 0;
float _speedAutoFill = 2.0f; // pixels per second

void autoLoop()
{
    // Set new rgb values
    if (!_isAnimRunning)
    {
        if (millis() - _timerAutoLoop > 4000)
        {
            int colIndx_ = floor(random(4)); // select random color component (0 for eraser)
            _timerAutoLoop = millis();
            _isAnimRunning = true;
            switch (colIndx_)
            {
            case 0: // Erase
                _targRed = 0;
                _targGreen = 0;
                _targBlue = 0;
                r = 0;
                g = 0;
                b = 0;
                break;
            case 1: // Red
                _targRed = floor(random(255));
                r = 0;
                break;
            case 2: // Green
                _targGreen = floor(random(255));
                g = 0;
                break;
            case 3: // Blue
                _targBlue = floor(random(255));
                b = 0;
                break;
            default:
                break;
            }
        }
    }

    // Play fill animation
    bool isRfill_ = r >= _targRed;
    bool isGfill_ = g >= _targGreen;
    bool isBfill_ = b >= _targBlue;
    if (!isRfill_)
    {
        isNewColor = true;
        r = floor(_targRed * _speedAutoFill * (millis() - _timerAutoLoop) / 1000.0f);
    }
    if (!isGfill_)
    {
        isNewColor = true;
        g = floor(_targGreen * _speedAutoFill * (millis() - _timerAutoLoop) / 1000.0f);
    }
    if (!isBfill_)
    {
        isNewColor = true;
        b = floor(_targBlue * _speedAutoFill * (millis() - _timerAutoLoop) / 1000.0f);
    }
    if (_isAnimRunning && (isRfill_ && isGfill_ && isBfill_))
    {
        _isAnimRunning = false;
        _timerAutoLoop = millis(); // reset timer to trig next r/g/b/eraser input
    }
}

void stopAutoLoop()
{
    _isAutoLoop = false;
    _targRed = 0;
    _targGreen = 0;
    _targBlue = 0;
    r = 0;
    g = 0;
    b = 0;
}