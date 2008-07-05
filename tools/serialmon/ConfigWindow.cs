// ------------------------------------------------------------------------------
//  <autogenerated>
//      This code was generated by a tool.
//      Mono Runtime Version: 2.0.50727.42
// 
//      Changes to this file may cause incorrect behavior and will be lost if 
//      the code is regenerated.
//  </autogenerated>
// ------------------------------------------------------------------------------

using System.IO.Ports;
using System;
namespace serialmon {
	
	
	public partial class ConfigWindow : Gtk.Window {
		bool xdone=false;
		            
		public ConfigWindow() : 
				base(Gtk.WindowType.Toplevel) {
			this.Build();
		}
		        public void configSetup(){
		            
		            if(xdone==false){
    			        updatePortNames();
    			        updatePortBaudrates();
    			        xdone=true;
    			    }
					colorbutton1.Color = MainClass.portcfg[0].color;
			        colorbutton2.Color = MainClass.portcfg[1].color;
			        cb_parity1.Active = (int)MainClass.portcfg[0].parity;
			        cb_parity2.Active = (int)MainClass.portcfg[1].parity;
			        cb_databits1.Active = (int)MainClass.portcfg[0].databits -5;
			        cb_databits2.Active = (int)MainClass.portcfg[1].databits -5;
			        cb_stopbits1.Active = (int)MainClass.portcfg[0].stopbits;
			        cb_stopbits2.Active = (int)MainClass.portcfg[1].stopbits;
			        checkbutton1.Active = MainClass.portcfg[0].active;
			        checkbutton2.Active = MainClass.portcfg[1].active;
			        fontbutton1.FontName = MainClass.mainfont;
			        colauto_rb.Active = MainClass.dataautowidth;
			        colgran_spin.Value = MainClass.datagran;
			        colwidth_spin.Value= MainClass.datafixwidth;
			        addrwidth_spin.Value = MainClass.addrwidth;
			        addrbasedec_rb.Active = (MainClass.addrBase=='D');
			        addrbasehex_rb.Active = (MainClass.addrBase=='X');
			        
		        }
		        
		        
		        protected virtual void  updatePortNames(){
			        string[] portnames;
                    int t;
			        portnames = System.IO.Ports.SerialPort.GetPortNames();
			        System.Console.WriteLine("Realized called");
			        foreach(string s in portnames){
				       cb_pn1.AppendText(s);
				       cb_pn2.AppendText(s);
				       System.Console.WriteLine("added serial port {0} to list", s);
					}
			
			        if((t=Array.FindIndex(portnames, MainClass.portcfg[0].portname.Equals))!=-1){
                       cb_pn1.Active=t;
			        } else {
				       cb_pn1.InsertText(0, MainClass.portcfg[0].portname);
				       cb_pn1.Active=0;
			        }
	       		    
			        if((t=Array.FindIndex(portnames, MainClass.portcfg[1].portname.Equals))!=-1){
                       cb_pn2.Active=t;
			        } else {
				       cb_pn2.InsertText(0, MainClass.portcfg[1].portname);
				       cb_pn2.Active=0;
			        }
			        
						
		        }
                
                protected virtual void  printInt(int v){
                    System.Console.WriteLine("\t {0}", v);
                }
                
		        protected virtual void  updatePortBaudrates(){
                    int t;
			        
			        if((t=Array.FindIndex(MainClass.baudrates, ((int)MainClass.portcfg[0].baudrate).Equals))!=-1){
                       cb_baudrate1.Active=t;
			        } else {
			            System.Console.WriteLine("baudrates: {0}", serialmon.MainClass.baudrates.Length.ToString());
			           Array.Resize(ref MainClass.baudrates, MainClass.baudrates.Length+1);
			           MainClass.baudrates[MainClass.baudrates.Length-1] = (int)MainClass.portcfg[1].baudrate;
			    
			         //MainClass.baudrates.S
			           MainClass.baudrates[MainClass.baudrates.Length-1] = (int)MainClass.portcfg[0].baudrate;
			         //  MainClass.baudrates += (int)MainClass.portcfg[0].baudrate;
				       cb_baudrate1.InsertText(0, MainClass.portcfg[0].baudrate.ToString());
				       cb_baudrate1.Active=0;
			           System.Console.WriteLine("baudrates: {0}", serialmon.MainClass.baudrates.Length.ToString());
			           Array.ForEach(MainClass.baudrates, printInt);
			        }
	       		    
			        if((t=Array.FindIndex(MainClass.baudrates, ((int)MainClass.portcfg[1].baudrate).Equals))!=-1){
                       cb_baudrate2.Active=t;
			        } else {
			         System.Console.WriteLine("baudrates: {0}", serialmon.MainClass.baudrates.Length.ToString());
			       
			         // MainClass.baudrates. (int)MainClass.portcfg[1].baudrate;
			           Array.Resize(ref MainClass.baudrates, MainClass.baudrates.Length+1);
			           MainClass.baudrates[MainClass.baudrates.Length-1] = (int)MainClass.portcfg[1].baudrate;
				       cb_baudrate2.InsertText(0, MainClass.portcfg[1].baudrate.ToString());
				       cb_baudrate2.Active=0;
			            System.Console.WriteLine("baudrates: {0}", serialmon.MainClass.baudrates.Length.ToString());
			        }
		        }


				protected virtual void OnCheckbutton1Released (object sender, System.EventArgs e)
				{
			        MainClass.portcfg[0].active = checkbutton1.Active;
			        MainClass.writeconfig();
				}

				protected virtual void OnCheckbutton2Released (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[1].active = checkbutton2.Active;
				    MainClass.writeconfig();
		        }

				protected virtual void OnCbPn1EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[0].portname = cb_pn1.ActiveText;
				    MainClass.writeconfig();
				}

				protected virtual void OnCbPn2EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[1].portname = cb_pn2.ActiveText;
				    MainClass.writeconfig();
				}

				protected virtual void OnCbBaudrate1EditingDone (object sender, System.EventArgs e)
				{
				    try{
				        MainClass.portcfg[0].baudrate = uint.Parse(cb_baudrate1.ActiveText);
				        MainClass.writeconfig();
				    }
				    catch{
				        MainClass.portcfg[0].baudrate = 9600;
				        MainClass.writeconfig();
				    }
				}

				protected virtual void OnCbBaudrate2EditingDone (object sender, System.EventArgs e)
				{
				    try{
				        MainClass.portcfg[1].baudrate = uint.Parse(cb_baudrate2.ActiveText);
				        MainClass.writeconfig();
				    }
				    catch{
				        MainClass.portcfg[1].baudrate = 9600;
				        MainClass.writeconfig();
				    }
				}

				protected virtual void OnCbParity1EditingDone (object sender, System.EventArgs e)
				{
			        MainClass.portcfg[0].parity = (Parity)(cb_parity1.Active);
				    MainClass.writeconfig();
				}

				protected virtual void OnCbParity2EditingDone (object sender, System.EventArgs e)
				{
			        MainClass.portcfg[1].parity = (Parity)(cb_parity2.Active);
				    MainClass.writeconfig();
				}

				protected virtual void OnColorbutton1ColorSet (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[0].color = colorbutton1.Color;
				    MainClass.writeconfig();
				}

				protected virtual void OnColorbutton2ColorSet (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[1].color = colorbutton2.Color;
				    MainClass.writeconfig();
				}

				protected virtual void OnCbDatabits1EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[0].databits = uint.Parse(cb_databits1.ActiveText);
				    MainClass.writeconfig();
				}

				protected virtual void OnCbDatabits2EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[1].databits = uint.Parse(cb_databits2.ActiveText);
				    MainClass.writeconfig();
				}

				protected virtual void OnCbStopbits1EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[0].stopbits = (StopBits)cb_stopbits1.Active;
				    MainClass.writeconfig();
				}
				
				protected virtual void OnCbStopbits2EditingDone (object sender, System.EventArgs e)
				{
				    MainClass.portcfg[1].stopbits = (StopBits)cb_stopbits2.Active;
				    MainClass.writeconfig();
				}

				protected virtual void OnOKButtonReleased (object sender, System.EventArgs e)
				{
				    MainClass.writeconfig();
				    MainClass.win.configfinished();
				    this.Destroy();
				}

				protected virtual void OnDestroyEvent (object o, Gtk.DestroyEventArgs args)
				{
				    serialmon.MainClass.win.configfinished();
				}

				protected virtual void OnDeleteEvent (object o, Gtk.DeleteEventArgs args)
				{
				    serialmon.MainClass.win.configfinished();
				}

				protected virtual void OnFontbutton1FontSet (object sender, System.EventArgs e)
				{
				    serialmon.MainClass.mainfont = fontbutton1.FontName;
				    MainClass.writeconfig();				    
				}

				protected virtual void OnColgranSpinValueChanged (object sender, System.EventArgs e)
				{
				    MainClass.datagran = (uint)colgran_spin.Value;
				    MainClass.writeconfig();				    
				}

				protected virtual void OnColwidthSpinValueChanged (object sender, System.EventArgs e)
				{
    				MainClass.datafixwidth = (uint)colwidth_spin.Value;
				    MainClass.writeconfig();
				}

				protected virtual void OnAddrwidthSpinValueChanged (object sender, System.EventArgs e)
				{
    				MainClass.addrwidth = (uint)addrwidth_spin.Value;
				    MainClass.writeconfig();
				}

				protected virtual void OnColautoRbGroupChanged (object sender, System.EventArgs e)
				{
				    MainClass.dataautowidth = colauto_rb.Active;
				    MainClass.writeconfig();
				}

				protected virtual void OnAddrbasehexRbGroupChanged (object sender, System.EventArgs e)
				{
				    if(addrbasedec_rb.Active)
    				    MainClass.addrBase = 'D';
    				if(addrbasehex_rb.Active)
    				    MainClass.addrBase = 'X';
				    MainClass.writeconfig();
				}

				
		
	}
}
