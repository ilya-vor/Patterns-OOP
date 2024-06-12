using Microsoft.VisualBasic.ApplicationServices;
using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography.Xml;

namespace Visitor
{
    abstract class CShape
    {
        public abstract void apply(CHandler handler);
        public virtual void addShape(CShape shape) { }

    }

    class CCircle : CShape
    {
        public CCircle(int x, int y)
        {
            _x = x;
            _y = y;
        }
        public int _x;
        public int _y;
        public override void apply(CHandler handler)
        {
            handler.handlePoint(this);
        }
    }

    class CGroup : CShape
    {
        public List<CShape> shapes = new List<CShape>();
        public override void apply(CHandler handler)
        {
            handler.handleGroup(this);
        }
        public override void addShape(CShape shape)
        {
            shapes.Add(shape);
        }
    }

    abstract class CHandler
    {
        public abstract void handlePoint(CCircle p);
        public void handleGroup(CGroup g)
        {
            foreach (CShape s in g.shapes)
            {
                s.apply(this);
            }
        }
    }

    class CDrawer: CHandler
    {
        private Graphics g;
        public CDrawer(Graphics g)
        {
            this.g = g;
        }
        public override void handlePoint(CCircle p)
        {
            
            int radius = 5;
            g.FillEllipse(Brushes.Black, p._x - radius, p._y - radius, radius * 2, radius * 2);
        }
    }

    class CMover: CHandler
    {
        private int dx;
        private int dy;
        public CMover(int dx, int dy)
        {
            this.dx = dx;
            this.dy = dy;
        }
        public override void handlePoint(CCircle p)
        {
            p._x = p._x + dx; 
            p._y = p._y + dy;
        }
    }

    public partial class Form1 : Form
    {
        CShape shapes = new CGroup();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            CCircle C = new CCircle(e.X, e.Y);
            shapes.addShape(C);
            pictureBox1.Invalidate();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            CDrawer drawer = new CDrawer(e.Graphics);
            shapes.apply(drawer);
            pictureBox1.Invalidate();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.A) { shapes.apply(new CMover(-5, 0)); }
            if (e.KeyCode == Keys.W) { shapes.apply(new CMover(0, -5)); }
            if (e.KeyCode == Keys.S) { shapes.apply(new CMover(0, 5)); }
            if (e.KeyCode == Keys.D) { shapes.apply(new CMover(5, 0)); }
            pictureBox1.Invalidate();
        }
    }
}
