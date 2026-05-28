using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace TextDisplay
{
    class Program
    {
	
        [STAThread]
        static void Main(string[] args)
        {
            string text = args.Length > 0 ? args[0] : "You need to enter your text!!!";
            Console.Title = text;

            string fontName = args.Length > 1 ? args[1] : "Segoe UI";
            float fontSize = args.Length > 2 ? float.Parse(args[2]) : 32f;

            Color textColor = Color.White;

            try
            {
                if (args.Length > 3)
                {
                    textColor = ColorTranslator.FromHtml(args[3]);
                }
            }
            catch
            {
                Console.WriteLine("Color not found or invalid");
                Console.ReadKey();
                Environment.Exit(0);
            }

            Color transparencyKey = Color.Lime;

            try
            {
                if (args.Length > 4)
                {
                    transparencyKey = ColorTranslator.FromHtml(args[4]);
                }
            }
            catch
            {
                Console.WriteLine("Color not found or invalid");
                Console.ReadKey();
                Environment.Exit(0);
            }

            int displayIndex = 0;

            try
            {
                if (args.Length > 5)
                {
                    displayIndex = int.Parse(args[5]);
                }
            }
            catch
            {
                Console.WriteLine("Display not found");
                Console.ReadKey();
                Environment.Exit(0);
            }

            Screen[] screens = Screen.AllScreens;

            if (displayIndex < 0 || displayIndex >= screens.Length)
            {
                Console.WriteLine("Display " + displayIndex +
                    " not found\nYour Connected displays: " +
                    screens.Length);
                Console.ReadKey();
                Environment.Exit(0);
            }

            OverlayPosition position = OverlayPosition.TopRight;

            if (args.Length > 6)
            {
                try
                {
                    position = (OverlayPosition)
                        Enum.Parse(
                            typeof(OverlayPosition),
                            args[6],
                            true);
                }
                catch
                {
                    Console.WriteLine(
                        "Invalid position.\n" +
                        "Valid values:\n" +
                        "TopLeft, TopCenter, TopRight,\n" +
                        "CenterLeft, Center, CenterRight,\n" +
                        "BottomLeft, BottomCenter, BottomRight");
                    Console.ReadKey();
                    Environment.Exit(0);
                    return;
                }
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Application.Run(new TextDisplayForm(
                text, fontName, fontSize, textColor, transparencyKey, screens[displayIndex], position));
        }
    }
}
