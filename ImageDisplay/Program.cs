using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Drawing;

namespace ImageDisplay
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            string imagePath = args[0];
            Console.Title = imagePath;

            if (!File.Exists(imagePath))
            {
                Console.WriteLine(
                    "Image not found:\n" + imagePath);
                Console.ReadKey();
                Environment.Exit(0);

                return;
            }

            Color transparencyKey = Color.White;

            try
            {
                if (args.Length > 1)
                {
                    transparencyKey = ColorTranslator.FromHtml(args[1]);
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
                if (args.Length > 2)
                {
                    displayIndex = int.Parse(args[2]);
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

            if (args.Length > 3)
            {
                try
                {
                    position = (OverlayPosition)
                        Enum.Parse(
                            typeof(OverlayPosition),
                            args[3],
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

            int sizePercent;

            if (!int.TryParse(args[4], out sizePercent))
            {
                Console.WriteLine("Invalid size percent.");
                Console.ReadKey();
                Environment.Exit(0);
                return;
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Application.Run(new ImageDisplayForm(
                imagePath, transparencyKey, screens[displayIndex], position, sizePercent));
        }
    }
}
