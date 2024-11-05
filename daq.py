from oscilloscopes import lecroy

_EVENTS = 10
_IP = "10.0.8.13"
_FILESUFFIX = "ejemplo"

#INIT
inst = lecroy( _IP, timeout=_EVENTS*1 ) #timeout in seconds
inst.clearAll()

#WINDOW SETUP
inst.setTime( hscale=10e-9, hdel=0, debug=True )
inst.setChannelOff( chn="C1" )
inst.setChannel(    chn="C2", vscale=0.200, voff=+0.600, debug=True )
inst.setChannel(    chn="C3", vscale=0.200, voff=+0.600, debug=True )
inst.setChannelOff( chn="C4" )
inst.setChannel(    chn="C5", vscale=0.500, voff=-1.500, debug=True )
inst.setChannelOff( chn="C6" )
inst.setChannelOff( chn="C7" )
inst.setChannelOff( chn="C8" )

#TRIGGER SETUP
inst.setTriggerLevel( chn="C5", slope="POS", lev=0.3, debug=True )
inst.setTriggerEdge( src="C5", debug=True )

#ACQUIRE
inst.setDisplay(0)
inst.acquire( cnt=_EVENTS, fileSuffix=_FILESUFFIX )
