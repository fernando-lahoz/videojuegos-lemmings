#include "geometry/bounding_box.hpp"
#include "geometry/point.hpp"

const int BLOCK_SIZE = 8;
#define BLOCK_TYPE u_int8_t


void handle_end_cases(
    std::vector<BLOCK_TYPE> &txt1_mask, 
    std::vector<BLOCK_TYPE> &txt2_mask,
    int h1_offset, int h2_offset,  
    int h1, int nBlocks, 
    Point2i block1, Point2i block2, 
    BLOCK_TYPE right_padding_mask1, BLOCK_TYPE right_padding_mask2,
    BLOCK_TYPE final_block_mask1, BLOCK_TYPE final_block_mask2,
    BLOCK_TYPE initial_offset1, BLOCK_TYPE initial_offset2,
    Point2i &collision_pixel1)
{
    int w1 = block1.x + nBlocks-2;
    int w2 = block2.x + nBlocks-2;

    BLOCK_TYPE alpha1 = txt1_mask[h1_offset + w1];
    BLOCK_TYPE alpha2 = txt2_mask[h2_offset + w2];

    alpha1 <<= initial_offset1;
    alpha2 <<= initial_offset2;

    /****** Generate paddings ******/
    BLOCK_TYPE alpha1_padding = 0;
    BLOCK_TYPE alpha2_padding = 0;
    
    alpha1_padding = txt1_mask[h1_offset + w1+1];
    alpha2_padding = txt2_mask[h2_offset + w2+1];

    alpha1_padding &= final_block_mask1;
    alpha2_padding &= final_block_mask2;


    // Get padding 1
    alpha1_padding >>= BLOCK_SIZE - initial_offset1;
    alpha1_padding &= right_padding_mask1;

    // Get padding 2
    alpha2_padding >>= BLOCK_SIZE - initial_offset2;
    alpha2_padding &= right_padding_mask2;

    // Add padding to alpha
    alpha1 |= alpha1_padding;
    alpha2 |= alpha2_padding;
    
    
    /************** Alpha comparison ***************/
    BLOCK_TYPE collision = alpha1 & alpha2;

    if (collision)
    {
        // clz, g++ only
        unsigned int bit_id = __builtin_clz(collision);
        unsigned int offset = initial_offset1 + bit_id;

        collision_pixel1 = Point2i(w1, h1);
        collision_pixel1.x = collision_pixel1.x*BLOCK_SIZE + offset; 
    }

    /****************** Handle final block case ***********************/
    w1 = block1.x + nBlocks-1;
    w2 = block2.x + nBlocks-1;

    alpha1 = txt1_mask[h1_offset + w1];
    alpha2 = txt2_mask[h2_offset + w2];

    alpha1 &= final_block_mask1;
    alpha2 &= final_block_mask2;

    alpha1 <<= initial_offset1;
    alpha2 <<= initial_offset2;

    collision = alpha1 & alpha2;

    if (collision)
    {
        // clz, g++ only
        unsigned int bit_id = __builtin_clz(collision);
        unsigned int offset = initial_offset1 + bit_id;

        collision_pixel1 = Point2i(w1, h1);
        collision_pixel1.x = collision_pixel1.x*BLOCK_SIZE + offset; 
    }
}


int main ()
{
    auto box_intersect = Bound2f(Point2f(0, 0), Point2f(1, 1));

    std::vector<BLOCK_TYPE> txt1_mask = {1, 0, 0, 0};
    std::vector<BLOCK_TYPE> txt2_mask = {1, 0, 0, 0};

    auto txt1_width = 2;
    auto txt2_width = 2;

    Point2i initial_pixel1 = Point2i(0);
    Point2i initial_pixel2 = Point2i(0);

    Point2i final_pixel1 = Point2i(15, 15);
    Point2i final_pixel2 = Point2i(15, 15);

    int box_width = final_pixel1.x - initial_pixel1.x;
    int box_height = final_pixel1.y - initial_pixel1.y;

    // Apply compression to the coordinates
    size_t initial_offset1 = initial_pixel1.x % BLOCK_SIZE;
    size_t initial_offset2 = initial_pixel2.x % BLOCK_SIZE;

    size_t final_offset1 = final_pixel1.x % BLOCK_SIZE;
    size_t final_offset2 = final_pixel2.x % BLOCK_SIZE;

    initial_pixel1.x -= initial_offset1;
    initial_pixel2.x -= initial_offset2;

    Point2i block1 = initial_pixel1;
    Point2i block2 = initial_pixel2;
    block1.x /= BLOCK_SIZE;
    block2.x /= BLOCK_SIZE;

    // Generate right padding mask
    BLOCK_TYPE right_padding_mask1 = (1 << initial_offset1) - 1; 
    BLOCK_TYPE right_padding_mask2 = (1 << initial_offset2) - 1;

    // Generate final block mask
    final_offset1 = final_offset1 - initial_offset1;

    BLOCK_TYPE final_block_mask1 = (1 << (BLOCK_SIZE-final_offset1)) - 1;
    BLOCK_TYPE final_block_mask2 = (1 << (BLOCK_SIZE-final_offset2)) - 1;

    int nBlocks = box_width / BLOCK_SIZE;
    if (box_width % BLOCK_SIZE != 0)
        nBlocks++;

    Point2i collision_pixel1(-1);

    for (int h = 0; h < box_height; h++)
    {
        int h1 = block1.y + h;
        int h1_offset = h1 * txt1_width;  

        int h2 = block2.y + h;
        int h2_offset = h2 * txt2_width;

        for (int w = 0; w < nBlocks-2; w++)
        {
            int w1 = block1.x + w;
            int w2 = block2.x + w;

            BLOCK_TYPE alpha1 = txt1_mask[h1_offset + w1];
            BLOCK_TYPE alpha2 = txt2_mask[h2_offset + w2];

            alpha1 <<= initial_offset1;
            alpha2 <<= initial_offset2;

            /****** Generate paddings ******/
            BLOCK_TYPE alpha1_padding = 0;
            BLOCK_TYPE alpha2_padding = 0;
            
            alpha1_padding = txt1_mask[h1_offset + w1+1];
            alpha2_padding = txt2_mask[h2_offset + w2+1];

            // Get padding 1
            alpha1_padding >>= BLOCK_SIZE - initial_offset1;
            alpha1_padding &= right_padding_mask1;

            // Get padding 2
            alpha2_padding >>= BLOCK_SIZE - initial_offset2;
            alpha2_padding &= right_padding_mask2;

            // Add padding to alpha
            alpha1 |= alpha1_padding;
            alpha2 |= alpha2_padding;
            
            
            /************** Alpha comparison ***************/
            BLOCK_TYPE collision = alpha1 & alpha2;

            if (collision)
            {
                std::cout << "Collision\n";

                // clz, g++ only
                unsigned int bit_id = __builtin_clz(collision);
                unsigned int offset = initial_offset1 + bit_id;

                collision_pixel1 = Point2i(w1, h1);
                collision_pixel1.x = collision_pixel1.x*BLOCK_SIZE + offset; 
            }
        }

        handle_end_cases(txt1_mask, txt2_mask,
            h1_offset, h2_offset,
            h1, nBlocks, 
            block1, block2, 
            right_padding_mask1, right_padding_mask2,
            final_block_mask1, final_block_mask2,
            initial_offset1, initial_offset2,
            collision_pixel1);
    }

    if (collision_pixel1.x != -1)
    {
        //collision_point.normal = e1->get_alpha_normal(collision_pixel1);
        std::cout << "Collision point" << ": " << collision_pixel1 << std::endl;
        exit(0);
    }

    //std::cout << "No collision\n";
}